#version 430
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;

out vec3 ourColor;

uniform mat4 mv;
uniform mat4 p;

void main(void)
{
	gl_Position = p * mv * vec4(pos, 1.0);
	ourColor = col;
}