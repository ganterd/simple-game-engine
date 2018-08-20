#version 430 core

in vec2 fragPosition;
out vec4 outColour;

uniform sampler2D positionsTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalsTexture;
uniform sampler2D diffuseTexture;
uniform sampler2D emissiveTexture;

uniform vec3 cameraPosition;

struct PointLight {
  vec4 position;
  vec4 colour;
  vec4 ambient;
};
buffer PointLightsBuffer{
    PointLight pointLights[];
};
uniform int numLights;


void main(){
    vec2 p = (fragPosition + vec2(1.0f)) * 0.5f;
    vec3 position = vec3(texture(positionsTexture, p));
    vec3 normal = vec3(texture(normalsTexture, p));
    vec3 specular = vec3(texture(specularTexture, p));
    vec3 diffuse = vec3(texture(diffuseTexture, p));

    vec3 finalColour = vec3(texture(emissiveTexture, p));
    for(int i = 0; i < numLights; ++i)
    {
        PointLight light = pointLights[i];
        vec3 lightPosition = vec3(light.position);
        vec3 lightColour = vec3(light.colour);
        vec3 lightAmbient = vec3(light.ambient);
        float lightPower = light.colour.w;

        vec3 viewDirection = normalize(cameraPosition - position);
        vec3 lightDirection = lightPosition - position;
        float lightDistance = length(lightDirection);
        lightDirection = normalize(lightDirection);

        /* Diffuse term */
        float lambertian = clamp(dot(normal, lightDirection), 0.0f, 1.0f);
        float falloff = lightPower / lightDistance;
        vec3 diffuseTerm = diffuse * lambertian * lightColour * falloff;

        /* Specular term */
        vec3 halfVector = normalize(viewDirection + lightDirection);
        float specularLambertian = clamp(dot(normal, halfVector), 0.0f, 1.0f);
        float specularIntensity = pow(specularLambertian, 16.0f);
        vec3 specularTerm = specular * lightColour * specularIntensity * falloff;

        /* Ambient term */
        vec3 ambientTerm = diffuse * lightAmbient;

        finalColour += diffuseTerm + specularTerm + ambientTerm;
    }
    outColour = vec4(finalColour, 1.0f);
}
