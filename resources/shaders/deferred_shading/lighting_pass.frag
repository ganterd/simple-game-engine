#version 430 core

in vec2 fragPosition;
out vec4 lightAccumulation;

uniform sampler2D inDiffuse;
uniform sampler2D inSpecular;
uniform sampler2D inPosition;
uniform sampler2D inNormal;
uniform sampler2D inLightAccumulation;
uniform vec3 inLightPosition;
uniform vec3 inLightColour;
uniform vec3 inLightAmbient;
uniform float inLightPower;
uniform int inLightHasShadowMap;
uniform mat4 inLightViewMatrix;
uniform sampler2D inLightShadowMap;
uniform vec3 cameraPosition;


void main(){
    vec2 p = (fragPosition + vec2(1.0f)) * 0.5f;
    vec3 diffuse = vec3(texture(inDiffuse, p));
    vec3 specular = vec3(texture(inSpecular, p));
    vec3 position = vec3(texture(inPosition, p));
    vec3 normal = vec3(texture(inNormal, p));
    vec3 finalColour = vec3(texture(inLightAccumulation, p));

    vec3 viewDirection = normalize(cameraPosition - position);
    vec3 lightDirection = inLightPosition - position;
    float lightDistance = length(lightDirection);
    lightDirection = normalize(lightDirection);

    if(inLightHasShadowMap == 1)
    {
		//finalColour += diffuse * inLightAmbient;
        vec4 lightMapPosition = inLightViewMatrix * vec4(position, 1.0f);
        if(lightMapPosition.x > -1.0f && lightMapPosition.x < 1.0f 
			&& lightMapPosition.y > -1.0f && lightMapPosition.y < 1.0f 
			&& lightMapPosition.z > -1.0f
		){
			vec2 lightMapPosition = (lightMapPosition.xy + vec2(1.0f)) * 0.5f;
			float depth = texture(inLightShadowMap, lightMapPosition).r;
			finalColour += vec3(depth);
        }
		else
		{
			/* Diffuse term */
			float lambertian = clamp(dot(normal, lightDirection), 0.0f, 1.0f);
			float falloff = inLightPower / lightDistance;
			vec3 diffuseTerm = diffuse * lambertian * inLightColour * falloff;

			/* Specular term */
			vec3 halfVector = normalize(viewDirection + lightDirection);
			float specularLambertian = clamp(dot(normal, halfVector), 0.0f, 1.0f);
			float specularIntensity = pow(specularLambertian, 16.0f);
			vec3 specularTerm = specular * inLightColour * specularIntensity * falloff;

			finalColour += diffuseTerm + specularTerm;
		}
	}
	lightAccumulation = vec4(finalColour, 1.0f);
}
