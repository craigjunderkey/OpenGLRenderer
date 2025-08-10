#version 430

out vec4 color;

in vec2 uv;

uniform sampler2D screenTexture;

void main()
{
	color = texture(screenTexture, uv);
}