#version 330 core

layout(location=0)in vec3 pos;
layout(location=1)in vec3 normal;
layout(location=2)in vec2 texture;

out vec2 texCoord;
out vec3 fragNormal;
out vec3 fragPos;
out vec3 frogPosRelativeViewSpace;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() 
{
    vec3 transformed_normal = mat3(transpose(inverse(model))) * vec3(normal);

    gl_Position = projection * view * model * vec4(pos.x, pos.y, pos.z, 1.0);
    texCoord = texture;
    fragNormal = normalize(transformed_normal);
    fragPos = vec3(model * vec4(pos.x, pos.y, pos.z, 1.0)); 
    frogPosRelativeViewSpace = vec3(view * vec4(fragPos, 1.0));
}
