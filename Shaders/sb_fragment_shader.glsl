#version 430
out vec4 color;

in vec2 uv;

uniform sampler2D atlas;

void main(void)
{
	color = texture(atlas, uv);
}