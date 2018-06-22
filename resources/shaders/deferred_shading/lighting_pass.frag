#version 430 core

in vec2 fragPosition;
out vec4 outColour;

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

    vec3 viewDirection = normalize(cameraPosition - position);
    vec3 lightDirection = lightPosition - position;
    float lightDistance = length(lightDirection);
    lightDirection = normalize(lightDirection);

    /* Diffuse term */
    float lambertian = clamp(dot(normal, lightDirection), 0.0f, 1.0f);
    float falloff = lightPower / lightDistance;
    diffuse = diffuse * lambertian * lightColour * falloff;

    /* Specular term */
    vec3 halfVector = normalize(viewDirection + lightDirection);
    float specularLambertian = clamp(dot(normal, halfVector), 0.0f, 1.0f);
    float specularIntensity = pow(specularLambertian, 16.0f);
    specular = specular * specularIntensity * falloff;
    //specular = vec3(specularIntensity);


    //finalColour = vec4(position * normal * specular * diffuse, 1.0f);

    vec3 finalColour = diffuse + specular;
    outColour = vec4(finalColour, 1.0f);
    //finalColour = vec4(vec3(falloff), 1.0f);
    //finalColour = vec4(vec3(position) * 0.5f, 1.0f);
}
