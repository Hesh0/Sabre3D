#version 430 core

attribute vec3 position;
// attribute vec2 texCoord; 

// varying vec2 texCoords; 

void main(void)
{
	gl_Position = vec4(position, 1);
	// texCoords = texCoord; 
}