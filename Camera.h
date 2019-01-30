#pragma once
#include "RigidBody.h"
#include "Transform.h"
#include <gl/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

class Camera
{
public:
	Camera();
	Camera(Transform& t, float zoom, float zNear, float zFar, float sens);
	~Camera();

	void update(milliseconds ms, int w, int h, double x, double y);

	void render();
	RigidBody rigidBody;
	vec3 center;
	vec3 up;
	mat3 rotMat;
	Transform transform;


private:
	int width;
	int height;
	float zoom;
	float zNear;
	float sens;
	float zFar;
	mat4 camMat;

};

