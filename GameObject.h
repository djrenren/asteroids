#pragma once
#include "Transform.h"
#include <string>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
#include "TextureManager.h"
#include "Model.h"
#include <memory>
#include "RigidBody.h"
#include "Collider.h"


using namespace std;
class GameObject
{

public:
	GameObject(shared_ptr<Transform> t, Model* m, string texture);

	GameObject(shared_ptr<Transform> t, Model* m, string texture, RigidBody& r);

	GameObject(shared_ptr<Transform> t, Model* m, string texture, RigidBody& r, Collider c);


	virtual void update(milliseconds ms) {
		transform->location += rigidBody.velocity;
		rigidBody.update(ms);
		transform->objectWorld = translate(this->transform->location) *
			yawPitchRoll(
				this->transform->rotation.x,
				this->transform->rotation.y,
				this->transform->rotation.z
				) * scale(transform->size);
	}

	virtual void render(TextureManager* tm) {
		glUniformMatrix4fv(3, 1, false, &(transform->objectWorld[0][0]));
		GLuint tex = tm->getTexture(textureFile);
		glBindTexture(GL_TEXTURE_2D, tex);
		model->render();
	}

	RigidBody rigidBody;

	bool collidesWith(const GameObject& other) {
		if (collider == Colliderless || other.collider == Colliderless) {
			return false;
		}
		if (collider == AABB && other.collider == AABB) {
			if (abs(transform->location.x - other.transform->location.x) < transform->size.x + other.transform->size.x &&
				abs(transform->location.y - other.transform->location.y) < transform->size.y + other.transform->size.y &&
				abs(transform->location.z - other.transform->location.z) < transform->size.z + other.transform->size.z) {
				return true;
			}
		}
		if (collider == Sphere && other.collider == Sphere) {
			if (length2(transform->location - other.transform->location) < pow((transform->size.x + other.transform->size.x), 2)) {
				return true;
			}
		}

		const Transform& aabb = *(collider == AABB ? *this : other).transform;
		const Transform& sphere = *(collider == Sphere ? *this : other).transform;

		// Code pulled from https://studiofreya.com/3d-math-and-physics/sphere-vs-aabb-collision-detection-test/
		auto check = [&](
			const double pn,
			const double bmin,
			const double bmax) -> double
		{
			double out = 0;
			double v = pn;

			if (v < bmin)
			{
				double val = (bmin - v);
				out += val * val;
			}

			if (v > bmax)
			{
				double val = (v - bmax);
				out += val * val;
			}

			return out;
		};

		double sq = 0;

		sq += check(sphere.location.x, aabb.location.x - aabb.size.x, aabb.location.x + aabb.size.x);
		sq += check(sphere.location.y, aabb.location.y - aabb.size.y, aabb.location.y + aabb.size.y);
		sq += check(sphere.location.z, aabb.location.z - aabb.size.z, aabb.location.z + aabb.size.z);

		if (sq < sphere.size.x * sphere.size.x) {
			return true;
		}

		return false;

	}

	string textureFile;
	GameObject();
	shared_ptr<Transform> transform;
	


protected:
	Model* model;
	GLuint texture;
	Collider collider;
};

