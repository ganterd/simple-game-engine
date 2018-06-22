#version 430 core

in vec2 fragPosition;
out vec4 finalColour;

uniform sampler2D positionsTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalsTexture;
uniform sampler2D albedoTexture;
uniform vec3 cameraPosition;

void main(){
    vec2 p = (fragPosition + vec2(1.0f)) * 0.5f;
    vec3 position = vec3(texture(positionsTexture, p));
    vec3 normal = vec3(texture(normalsTexture, p));
    vec3 specular = vec3(texture(specularTexture, p));
    vec3 diffuse = vec3(texture(albedoTexture, p));

    vec3 lightPosition = vec3(0.0f, 2.0f, 0.0f);
    vec3 lightColour = vec3(1.0f, 1.0f, 1.0f);
    float lightPower = 3.0f;

    vec3 lightDirection = lightPosition - position;
    //vec3 lightDirection = vec3(0.0f, 1.0f, 0.0f);
    float lightDistance = length(lightDirection);
    lightDirection = normalize(lightDirection);

    float lambertian = clamp(dot(normal, lightDirection), 0.0f, 1.0f);
    float falloff = lightPower / lightDistance;
    //diffuse *= lambertian * lightColour * lightPower / lightDistance;

    //finalColour = vec4(position * normal * specular * diffuse, 1.0f);
    finalColour = vec4(vec3(diffuse * lambertian * falloff), 1.0f);
    //finalColour = vec4(vec3(falloff), 1.0f);
    //finalColour = vec4(vec3(position) * 0.5f, 1.0f);
}
