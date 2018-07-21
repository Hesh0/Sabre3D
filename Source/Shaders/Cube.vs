#version 430 core

in vec4 position;
out vec4 color;

void main(void)
{
	gl_Position = position;
	color = position * 2 + vec4(0.2, 0.3, 0.2, 0.0);
}