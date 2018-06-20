#version 330 core

in vec4 gl_FragCoord;
in vec3 fragNormal;

layout (location = 0) out vec4 color;

float near = 0.1f;
float far = 10.0f;

float ToCameraDepth(float d)
{
    float z = d * 2.0f - 1.0f;
    return (2.0f * near * far) / (far + near - z * (far - near)) / far;
}

void main(){
    float depth = ToCameraDepth(gl_FragCoord.z);
    color = vec4(depth, depth, depth, 1.0f);
}
