#version 430 core

uniform sampler2D samp;
varying vec2 texCoords;

// out vec4 color;

void main(void)
{
	gl_FragColor = texture2D(samp, texCoords); 
}