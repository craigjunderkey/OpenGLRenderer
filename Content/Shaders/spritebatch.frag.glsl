#version 430
out vec4 color;

in vec2 uv;
in vec3 tint;

uniform sampler2D atlas;

void main()
{
	color = texture(atlas, uv);
	color.xyz *= tint;
}