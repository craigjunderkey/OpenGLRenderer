#version 430
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 vertexUv;
layout (location = 2) in mat4 m;
layout (location = 6) in vec4 uvBounds;

uniform mat4 v;
uniform mat4 p;

out vec2 uv;

void main(void)
{
	gl_Position = p * v * m * vec4(pos, 1.0);
	uv = mix(uvBounds.xy, uvBounds.zw, vertexUv);
	uv.y = 1 - uv.y; // un-flip our sprites
}