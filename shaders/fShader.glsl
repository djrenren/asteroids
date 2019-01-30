#version 430
in vec2 uv;
in vec3 norm;
in vec3 loc;

// Values that stay constant for the whole mesh.
uniform sampler2D myTexture;
in vec3 f_cameraLoc;
in vec3 f_lightLoc;

void main()
{

	vec3 norm2 = normalize(norm);
	vec3 L = normalize(f_lightLoc - loc);
	vec3 E = normalize(f_cameraLoc - loc);
	vec3 H = normalize(L + E);

	float ambient = .4;
	float diffuse = .5 * max(dot(L,norm2), 0);
	float specular = 5 * pow(max(dot(H,norm2), 0), 16);
	gl_FragColor = texture(myTexture, uv) * (ambient + diffuse + specular);

}