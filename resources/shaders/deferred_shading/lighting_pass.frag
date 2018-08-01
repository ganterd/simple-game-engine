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
};
layout(std430, binding = 10) buffer TrisBuffer{ Tri tris[]; };

struct BVHNode {
    int leftIdx;
    int rightIdx;
    bool isLeaf;
    vec4 aabbMin;
    vec4 aabbMax;
};
layout(std430, binding = 11) buffer BVHNodesBuffer{ BVHNode nodes[]; };

void main(){
    vec2 p = (fragPosition + vec2(1.0f)) * 0.5f;
    vec3 position = vec3(texture(positionsTexture, p));
    vec3 normal = vec3(texture(normalsTexture, p));
    vec3 specular = vec3(texture(specularTexture, p));
    vec3 diffuse = vec3(texture(albedoTexture, p));

    vec3 finalColour = diffuse;
    //vec3 lightPosition = vec3(0.0f, 2.0f, 0.0f);
    //vec3 finalColour = vec3(texture(emmisiveTexture, p));
    // for(int i = 0; i < numLights; ++i)
    // {
    //     PointLight light = pointLights[i];
    //     vec3 lightPosition = vec3(light.position);
    //     vec3 lightColour = vec3(light.colour);
    //     float lightPower = light.colour.w;
    //
    //     vec3 viewDirection = normalize(cameraPosition - position);
    //     vec3 lightDirection = lightPosition - position;
    //     float lightDistance = length(lightDirection);
    //     lightDirection = normalize(lightDirection);
    //
    //     /* Diffuse term */
    //     float lambertian = clamp(dot(normal, lightDirection), 0.0f, 1.0f);
    //     float falloff = lightPower / lightDistance;
    //     vec3 diffuseTerm = diffuse * lambertian * lightColour * falloff;
    //
    //     /* Specular term */
    //     vec3 halfVector = normalize(viewDirection + lightDirection);
    //     float specularLambertian = clamp(dot(normal, halfVector), 0.0f, 1.0f);
    //     float specularIntensity = pow(specularLambertian, 16.0f);
    //     vec3 specularTerm = specular * lightColour * specularIntensity * falloff;
    //
    //     finalColour += diffuseTerm + specularTerm;
    // }
    outColour = vec4(finalColour, 1.0f);
    //finalColour = vec4(vec3(falloff), 1.0f);
    //finalColour = vec4(vec3(position) * 0.5f, 1.0f);
}
