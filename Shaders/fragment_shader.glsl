#version 430
out vec4 color;
in vec3 ourColor;

void main(void)
{
	color = vec4(ourColor, 1.0);
}