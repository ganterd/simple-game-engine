#version 430 core

in vec3 fragNormal;
in vec3 fragPosition;
in vec2 fragTexCoord;
in mat3 normalMapTransform;

uniform sampler2D albedoTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalsTexture;
uniform sampler2D opacityTexture;
uniform sampler2D emissiveTexture;

uniform bool hasNormalMap;
uniform bool hasOpacityMap;
uniform bool hasEmmisiveTexture;

out vec4 outDiffuse;
out vec4 outSpecular;
out vec4 outNormals;
out vec4 outPositions;
out vec4 outEmissive;

void main(){
    vec3 normal = fragNormal;
    if(hasNormalMap)
    {
        normal = vec3(texture(normalsTexture, fragTexCoord));
        normal = normalize(normal * 2.0f - 1.0f);
        normal = normalize(normalMapTransform * normal);
    }

    float opacity = 1.0f;
    if(hasOpacityMap)
    {
        opacity = texture(opacityTexture, fragTexCoord).r;
        if(opacity < 1.0f)
            discard;
    }

    outPositions = vec4(fragPosition, opacity);
    outNormals = vec4(normal, opacity);
    outDiffuse = vec4(vec3(texture(albedoTexture, fragTexCoord)), opacity);
    outSpecular = vec4(vec3(texture(specularTexture, fragTexCoord)), opacity);

    if(hasEmmisiveTexture)
        outEmissive = vec4(vec3(texture(emissiveTexture, fragTexCoord)), opacity);
    else
        outEmissive = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}
