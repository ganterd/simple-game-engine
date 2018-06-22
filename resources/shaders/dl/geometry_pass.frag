#version 430 core

in vec3 fragNormal;
in vec3 fragPosition;
in vec2 fragTexCoord;
in mat3 normalMapTransform;

layout (binding = 0) uniform sampler2D albedoTexture;
layout (binding = 1) uniform sampler2D normalsTexture;
layout (binding = 2) uniform sampler2D opacityTexture;

uniform bool hasNormalMap;
uniform bool hasOpacityMap;

layout (location = 0) out vec4 positionGBuffer;
layout (location = 1) out vec4 normalGBuffer;
layout (location = 2) out vec4 albedoGBuffer;

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

    positionGBuffer = vec4(fragPosition, opacity);
    normalGBuffer = vec4(normal, opacity);
    albedoGBuffer = vec4(vec3(texture(albedoTexture, fragTexCoord)), opacity);
}
