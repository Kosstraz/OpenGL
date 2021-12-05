#version 330 core
layout (location = 0) in vec3 aPos; // La variable position a l'attribut de position 0
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
  
out vec2 texCoord;
out vec3 vertexColor;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0); // un vec3 est utilisé pour construire un vec4
    vertexColor = aColor;//vec3(1.0f,0.5f,0.2f); // Couleur rouge foncé
    texCoord = vec2(aTexCoord.x, aTexCoord.y);
}