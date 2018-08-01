#version 430 core

in vec2 fragPosition;
out vec4 outColour;

layout (binding = 0) uniform sampler2D positionsTexture;
layout (binding = 1) uniform sampler2D specularTexture;
layout (binding = 2) uniform sampler2D normalsTexture;
layout (binding = 3) uniform sampler2D albedoTexture;
layout (binding = 4) uniform sampler2D emmisiveTexture;

uniform vec3 cameraPosition;

struct PointLight {
  vec4 position;
  vec4 colour;
};
layout(std430, binding = 9) buffer PointLightsBuffer{ PointLight pointLights[]; };
uniform int numLights;

struct Tri{
    vec4 v0;
    vec4 v1;
    vec4 v2;
    vec4 pad;
};
layout(std430, binding = 10) buffer TrisBuffer{ Tri tris[]; };

struct BVHNode {
    vec4 aabbMin;
    vec4 aabbMax;
    int leftIdx;
    int rightIdx;
    int isLeaf;
    int parentIdx;
};
layout(std430, binding = 11) buffer BVHNodesBuffer{ BVHNode nodes[]; };

bool testAABB(vec3 rayOrigin, vec3 rayDirection, vec3 aabbMin, vec3 aabbMax)
{
    float tmin = (aabbMin.x - rayOrigin.x) / rayDirection.x;
    float tmax = (aabbMax.x - rayOrigin.x) / rayDirection.x;

    if (tmin > tmax)
    {
        float t = tmin;
        tmin = tmax;
        tmax = t;
    }

    float tymin = (aabbMin.y - rayOrigin.y) / rayDirection.y;
    float tymax = (aabbMax.y - rayOrigin.y) / rayDirection.y;

    if (tymin > tymax)
    {
        float t = tymin;
        tymin = tymax;
        tymax = t;
    }

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax;

    float tzmin = (aabbMin.z - rayOrigin.z) / rayDirection.z;
    float tzmax = (aabbMax.z - rayOrigin.z) / rayDirection.z;

    if (tzmin > tzmax)
    {
        float t = tzmin;
        tzmin = tzmax;
        tzmax = t;
    }

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;

    if (tzmax < tmax)
        tmax = tzmax;

    return true;
}

bool testTri(
    in int triIdx,
    in vec3 rayOrigin,
    in vec3 rayDirection,
    inout float hitDistance,
    out vec3 hitNormal
){
    const float e = 0.000001f;
    vec3 v0, edge1, edge2;
	vec3 tvec, pvec, qvec;
	float det, inv_det;

    v0 = vec3(tris[triIdx].v0);
    edge1 = vec3(tris[triIdx].v1) - v0;
    edge2 = vec3(tris[triIdx].v2) - v0;

	pvec = cross(rayDirection, edge2);
	det = dot(edge1, pvec);

	if(det > -e && det < e)
		return false;
	inv_det = 1.0f / det;

	tvec = rayOrigin - v0;
	float u = dot(tvec, pvec) * inv_det;
	if(u < 0.0f || u > 1.0f)
		return false;

	qvec = cross(tvec, edge1);
	float v = dot(rayDirection, qvec) * inv_det;
	if(v < 0.0f || (u + v > 1.0f))
		return false;

	float d = dot(edge2, qvec) * inv_det;
	if(d < e)
		return false;

	hitDistance = d;
    hitNormal = normalize(cross(edge1, edge2));
	return true;
}

int getNextSearchNode(int currentNode)
{
    while(true)
    {
        int parentIdx = nodes[currentNode].parentIdx;
        if(parentIdx == -1)
            return -1;

        if(nodes[parentIdx].leftIdx == currentNode)
        {
            return nodes[parentIdx].rightIdx;
        }
        else if(nodes[parentIdx].rightIdx == currentNode)
        {
            currentNode = parentIdx;
        }
    }
}

int traverse(
    in vec3 rayOrigin,
    in vec3 rayDirection,
    in float maxDistance,
    inout int nodesTested,
    out float hitDistance,
    out vec3 hitNormal
){
    int nodeIdx = 0;
    bool checkLeft = true;
    int hits = 0;
    hitDistance = 100000;

    while(nodesTested < 10000 && nodeIdx >= 0)
    {
        vec3 aabbMin = vec3(nodes[nodeIdx].aabbMin);
        vec3 aabbMax = vec3(nodes[nodeIdx].aabbMax);
        nodesTested++;
        if(!testAABB(rayOrigin, rayDirection, aabbMin, aabbMax))
        {
            nodeIdx = getNextSearchNode(nodeIdx);
        }
        else
        {
            if(nodes[nodeIdx].isLeaf != 0)
            {
                float testHitDistance;
                vec3 testHitNormal;
                if(testTri(nodes[nodeIdx].leftIdx, rayOrigin, rayDirection, testHitDistance, testHitNormal))
                {
                    hits++;
                    if(testHitDistance < hitDistance)
                    {
                        hitDistance = testHitDistance;
                        hitNormal = testHitNormal;
                    }
                }

                if(nodes[nodeIdx].rightIdx > 0)
                {
                    if(testTri(nodes[nodeIdx].rightIdx, rayOrigin, rayDirection, testHitDistance, testHitNormal))
                    {
                        hits++;
                        if(testHitDistance < hitDistance)
                        {
                            hitDistance = testHitDistance;
                            hitNormal = testHitNormal;
                        }
                    }
                }
                nodeIdx = getNextSearchNode(nodeIdx);
            }
            else
            {
                nodeIdx = nodes[nodeIdx].leftIdx;
            }
        }
    }
    return hits;
}

bool occluded(in vec3 a, in vec3 b, inout int nodesTested)
{
    vec3 dir = b - a;
    float d = length(dir);
    dir = normalize(dir);
    vec3 p = a + 0.0001f * d;
    float hitDistance;
    vec3 hitNormal;
    if(traverse(p, dir, d, nodesTested, hitDistance, hitNormal) > 0)
        return hitDistance < d;
    return false;
}

void main(){
    vec2 p = (fragPosition + vec2(1.0f)) * 0.5f;
    vec3 position = vec3(texture(positionsTexture, p));
    vec3 normal = vec3(texture(normalsTexture, p));
    vec3 specular = vec3(texture(specularTexture, p));
    vec3 diffuse = vec3(texture(albedoTexture, p));


    vec3 lightPosition = vec3(pointLights[0].position);

    vec3 rayDirection = normalize(position - cameraPosition);
    float hitDistance;
    vec3 hitNormal;
    int nodesTested = 0;

    vec3 finalColour;
    int hits = traverse(cameraPosition, rayDirection, 10000.0f, nodesTested, hitDistance, hitNormal);
    if(hits > 0)
    {
        vec3 hitPosition = rayDirection * hitDistance * 0.999f + cameraPosition;
        int occlusionNodesTested = 0;
        if(!occluded(hitPosition, lightPosition, occlusionNodesTested))
        {
            vec3 lightDirection = lightPosition - hitPosition;
            float lightDistance = length(lightPosition - hitPosition);
            lightDirection = normalize(lightDirection);
            float lightPower = pointLights[0].colour.w;
            float falloff = lightPower / lightDistance;
            float lambertian = clamp(dot(hitNormal, lightDirection), 0.0f, 1.0f);
            vec3 diffuseTerm = vec3(0.8f, 0.8f, 0.8f) * falloff * vec3(pointLights[0].colour) * lambertian;
            finalColour += diffuseTerm;
        }
    }

    outColour = vec4(finalColour, 1.0f);
}
