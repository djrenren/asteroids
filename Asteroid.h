#pragma once
#define GLM_SWIZZLE

#include "GameObject.h"
#include <glm/glm.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>
#include "ObjModel.h"
class Asteroid :
	public GameObject
{
public:
	Asteroid(shared_ptr<Transform> t, Model* m, string texture, RigidBody& r, Collider c);
	~Asteroid();


	static Asteroid* random(vec3 target, float fuzziness, int minDistance, int maxDistance);
	static void bufferModels();

private:
	static vec3 genPositionInRadius(vec3& pos, float radius);
	static vector<Model*> asteroidModels;
	static vector<string> asteroidTextures;
};

