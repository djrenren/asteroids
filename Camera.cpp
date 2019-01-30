#include "Camera.h"


Camera::Camera()
{
}

Camera::Camera(Transform & t, float zoom, float zNear, float zFar, float sens)
	:transform(t), zoom(zoom), zNear(zNear), zFar(zFar), sens(sens)
{
	rigidBody = RigidBody{ {0,0,0}, {0,0,0 }, 1 };
}

Camera::~Camera()
{
}

void Camera::update(milliseconds ms, int w, int h, double x, double y)
{
	width = w;
	height = h;
	transform.location += rigidBody.velocity;
	rigidBody.update(ms);

	transform.rotation.y -= sens * (x - w * .5f);
	transform.rotation.x -= sens * (y - h * .5f);

	

	rotMat = (mat3)yawPitchRoll(transform.rotation.y, transform.rotation.x, transform.rotation.z);

	vec3 eye = transform.location;
	center = eye + rotMat * vec3(0, 0, -1);
	up = rotMat * vec3(0, 1, 0);

	mat4 lookatMat = glm::lookAt(eye, center, up);

	float fovy = M_PI * .4f / zoom;
	float aspect = (float)width / (float)height;


	mat4 perspectiveMat = glm::perspective(fovy, aspect, zNear, zFar);

	camMat = perspectiveMat * lookatMat;
}

void Camera::render()
{
	glUniformMatrix4fv(4, 1, GL_FALSE, &camMat[0][0]);
	glUniformMatrix4fv(5, 1, GL_FALSE, &vec3(0,0,0)[0]);

}
