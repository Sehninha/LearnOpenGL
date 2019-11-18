#version 330 core

out vec4 fragmentColor;
in vec2 uv;

uniform sampler2D textureSample;

void main()
{
	fragmentColor = texture(textureSample, uv);
}