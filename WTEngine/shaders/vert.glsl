#version 330 core

layout(location=0)in vec3 pos;
layout(location=1)in vec3 color;
layout(location=2)in vec2 texture;

out vec4 pixelColor;
out vec2 texCoord;

void main() 
{
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
    pixelColor = vec4(color, 1.0);
    texCoord = texture;
}
