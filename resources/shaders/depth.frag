#version 330 core

in vec4 gl_FragCoord;

varying vec3 fragNormal;
out vec3 color;
 
void main(){
    color = vec3(
    	clamp(gl_FragCoord.z * 0.2, 0, 1),
    	clamp(gl_FragCoord.z * 0.2, 0, 1),
    	clamp(gl_FragCoord.z * 0.2, 0, 1)
    );
}
