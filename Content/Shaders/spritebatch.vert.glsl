#version 430
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 vertexUv;
layout (location = 2) in mat4 m;
layout (location = 6) in vec4 uvBounds;
layout (location = 7) in uint tintAndFlags;

uniform mat4 v;
uniform mat4 p;

out vec2 uv;
out vec3 tint;

void main(void)
{
	// transform vertex position
	gl_Position = p * v * m * vec4(pos, 1.0);

	// calculate uv bounds w.r.t. flags
	vec4 finalUvBounds = uvBounds;
	if ((tintAndFlags & 0x01) == 0x01)	// h-flip
		finalUvBounds.xz = uvBounds.zx; 
	if ((tintAndFlags & 0x02) == 0x02)  // v-flip
		finalUvBounds.yw = uvBounds.wy;

	uv = mix(finalUvBounds.xy, finalUvBounds.zw, vertexUv);
	
	// (un-)flip our spritesheet vertically
	uv.y = 1 - uv.y; 

	// calculate tint
	uint red 	= (tintAndFlags & 0xFF000000u) >> 24;
	uint green 	= (tintAndFlags & 0x00FF0000u) >> 16;
	uint blue 	= (tintAndFlags & 0x0000FF00u) >> 8;
	tint = vec3(red, green, blue) / 255.0;
}