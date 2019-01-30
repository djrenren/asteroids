#version 430
in vec3 texCoord;

// Values that stay constant for the whole mesh.
uniform samplerCube cubeTex;
void main()
{
	gl_FragColor = texture(cubeTex, texCoord);

}