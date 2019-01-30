#pragma once
#include <glm/glm.hpp>
using namespace glm;

struct Transform {
	vec3 location, rotation, size;
	mat4 objectWorld;
};