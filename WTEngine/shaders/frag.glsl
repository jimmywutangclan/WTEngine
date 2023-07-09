#version 330 core

out vec4 FragColor;
in vec2 texCoord;

uniform sampler2D diffuse1;
uniform sampler2D diffuse2;

void main()
{
    FragColor = texture(diffuse1, texCoord);
} 