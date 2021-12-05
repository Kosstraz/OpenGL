#version 330 core

out vec4 FragColor;

in vec2 texCoord;

uniform float opacity;
uniform vec2 texture1Offset;
uniform vec2 texture2Offset;
uniform vec3 vertexColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, texCoord+texture1Offset), texture(texture2, texCoord+texture2Offset), opacity);
}