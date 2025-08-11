#version 430

out vec4 color;

in vec2 uv;

uniform sampler2D screenTexture;

void main()
{
	color = texture(screenTexture, uv);
	float avg = (color.x + color.y + color.z) / 3.0;
	color.xyz = vec3(avg, avg, avg);
}