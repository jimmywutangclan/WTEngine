#version 330 core

out vec4 FragColor;
in vec2 texCoord;
in vec3 fragNormal;
in vec3 fragPos;
in vec3 frogPosRelativeViewSpace;

uniform sampler2D diffuse1;
uniform sampler2D diffuse2;

void main()
{
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 ambient = 0.05 * lightColor;

    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(vec3(2, 2, 2) - fragPos);
    float lightingAngle = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = lightingAngle * lightColor;

    // all of this is done relative to view
    float specularStrength = 0.8;
    vec3 viewDir = normalize(frogPosRelativeViewSpace);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
    vec3 specular = specularStrength * spec * lightColor;  


    FragColor = vec4((ambient + diffuse + specular) * texture(diffuse1, texCoord).rgb, 1.0);
} 