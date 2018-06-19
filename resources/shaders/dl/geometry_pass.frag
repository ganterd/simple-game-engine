#version 330 core

varying vec3 fragNormal;
//out vec3 color;
 
void main(){
    gl_FragColor = vec4(
    	clamp(fragNormal.x, 0, 1),
    	clamp(fragNormal.y, 0, 1),
    	clamp(fragNormal.z, 0, 1),
    	1
    );
}
