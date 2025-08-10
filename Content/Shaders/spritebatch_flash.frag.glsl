#version 430
out vec4 color;

in vec2 uv;
in vec3 tint;

uniform sampler2D atlas;
uniform float time;
uniform float speed;

void main()
{
	color = texture(atlas, uv);
	color.xyz = mix(color.xyz, tint, 0.5 * sin(speed * time) + 0.5);
}