// uniform sampler2D samp;
// varying vec2 texCoords;

out vec4 color;

void main(void)
{
	// gl_FragColor = texture2D(samp, texCoords); 
	color = vec4(0.0, 0.8, 1.0, 1.0);
}