#version 330

in vec2 vPosition;

varying vec3 fragPosition;

void main()
{
	vec4 v = vec4(vPosition, 0.0f, 0.0f);
	fragPosition = vPosition;
	gl_Position = v;
}
