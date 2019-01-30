#pragma once
#include "GameObject.h"
#include "ObjModel.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>

class Skybox
{
public:
	Skybox(float dim, GLuint texture);
	~Skybox();

	void render();

	Transform transform;

private:

	GLuint texture;
	Model* model;
};

