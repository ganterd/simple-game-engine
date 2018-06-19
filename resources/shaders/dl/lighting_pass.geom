#version 330 core

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

out vec2 texcoord;
out vec2 screen_position;

void main() 
{
    gl_Position = vec4( 1.0, 1.0, 0.5, 1.0 );
    texcoord = vec2( 1.0, 1.0 );
    screen_position = vec2(1.0f, 1.0f);
    EmitVertex();

    gl_Position = vec4(-1.0, 1.0, 0.5, 1.0 );
    texcoord = vec2( 0.0, 1.0 ); 
    screen_position = vec2(0.0f, 1.0f);
    EmitVertex();

    gl_Position = vec4( 1.0,-1.0, 0.5, 1.0 );
    texcoord = vec2( 1.0, 0.0 ); 
    screen_position = vec2(1.0f, 0.0f);
    EmitVertex();

    gl_Position = vec4(-1.0,-1.0, 0.5, 1.0 );
    texcoord = vec2( 0.0, 0.0 ); 
    screen_position = vec2(0.0f, 0.0f);
    EmitVertex();

    EndPrimitive(); 
}
