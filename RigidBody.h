#pragma once
#include <glm/glm.hpp>
#include <chrono>
using namespace std::chrono;
struct RigidBody {
	glm::vec3 velocity, force;
	float mass;

	void update(milliseconds ms) {
		if (ms > milliseconds(0)) {
			velocity += force / (mass * ms.count());
		}
		force = { 0,0,0 };
	}
};