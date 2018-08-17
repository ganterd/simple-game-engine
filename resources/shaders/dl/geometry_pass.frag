#version 430 core

in vec3 fragNormal;
in vec3 fragPosition;
in vec2 fragTexCoord;
in mat3 normalMapTransform;

uniform sampler2D albedoTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalsTexture;
uniform sampler2D opacityTexture;

uniform bool hasNormalMap;
uniform bool hasOpacityMap;
uniform bool hasEmmisiveTexture;

/*layout (location = 0) */out vec4 diffuse;
/*layout (location = 1) */out vec4 specular;
/*layout (location = 3) */out vec4 positions;
/*layout (location = 2) */out vec4 normals;
/*layout (location = 4) */out vec4 emissive;

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

    positions = vec4(fragPosition, opacity);
    normals = vec4(normal, opacity);
    diffuse = vec4(vec3(texture(albedoTexture, fragTexCoord)), opacity);
    specular = vec4(vec3(texture(specularTexture, fragTexCoord)), opacity);
}
