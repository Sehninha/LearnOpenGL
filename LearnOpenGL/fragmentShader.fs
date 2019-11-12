#version 330 core

out vec4 fragmentColor;
in vec3 color;
in vec2 uv;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	fragmentColor = mix(texture(texture1, uv), texture(texture2, uv), 0.2) * vec4(color, 1.0);
}