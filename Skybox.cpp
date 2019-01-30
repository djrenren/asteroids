#include "Skybox.h"



Skybox::Skybox(float dim, GLuint texture) : texture(texture)
{
	transform = Transform{
		{0,0,0},
		{0,0,0},
		vec3(1,1,1) * (float)dim
	};




	model = new ObjModel("models/box.obj");
}

Skybox::~Skybox()
{
}


void Skybox::render()
{
	transform.objectWorld = translate(transform.location) *
		yawPitchRoll(
			transform.rotation.x,
			transform.rotation.y,
			transform.rotation.z
			) * scale(transform.size);
	glUniformMatrix4fv(3, 1, false, &(transform.objectWorld[0][0]));
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	model->render();
}

