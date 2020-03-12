#version 450 core

out vec4 FragColor;
in vec2 texCoor;

uniform sampler2D textureLoader;

void main()
{
	FragColor = texture(textureLoader, texCoor);
} 