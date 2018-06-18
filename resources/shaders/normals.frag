#version 330 core

varying vec3 fragNormal;
out vec3 color;
 
void main(){
    color = vec3(
    	clamp(fragNormal.x, 0, 1),
    	clamp(fragNormal.y, 0, 1),
    	clamp(fragNormal.z, 0, 1)
    );
}
