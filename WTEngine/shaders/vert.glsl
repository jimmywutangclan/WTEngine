#version 330 core

layout(location=0)in vec3 pos;
layout(location=1)in vec2 texture;

out vec2 texCoord;

uniform mat4 transform;

void main() 
{
    gl_Position = transform * vec4(pos.x, pos.y, pos.z, 1.0);
    texCoord = texture;
}
