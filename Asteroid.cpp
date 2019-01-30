#include "Asteroid.h"


Asteroid::Asteroid(shared_ptr<Transform> t, Model * m, string texture, RigidBody & r, Collider c) :
	GameObject(t, m, texture, r, c)
{

}


Asteroid::~Asteroid()
{
}

Asteroid* Asteroid::random(vec3 target, float fuzziness, int minDistance, int maxDistance)
{

	vec3 astPos = genPositionInRadius(target, rand() % (maxDistance - minDistance + 1) + minDistance);
	vec3 astTarget = genPositionInRadius(target, fuzziness);
	float speed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 3 + 1;
	int size = rand() % 40 + 15;
	return new Asteroid(
		make_shared<Transform>(Transform{
		astPos,
		{ rand() * M_2_PI, rand() * M_2_PI, rand() * M_2_PI },
		{ size, size, size }
	}),
		asteroidModels[rand() % 30],
		asteroidTextures[rand() % asteroidTextures.size()],
		RigidBody{ normalize(astTarget - astPos) * speed, vec3(0,0,0), 1 },
		Sphere
		);
}

vec3 Asteroid::genPositionInRadius(vec3 & pos, float radius)
{

		return pos + (yawPitchRoll((float)(rand() * M_2_PI), (float)(rand() * M_2_PI), (float)(rand() * M_2_PI)) * vec4(1, 0, 0, 1)).xyz() * radius;
}

void Asteroid::bufferModels()
{
	if (asteroidModels.size() == 0) {
		for (int i = 1; i < 31; i++) {
			asteroidModels.emplace_back(new ObjModel("models/asteroid" + to_string(i) + ".obj"));
		}
	}
}


vector<string> Asteroid::asteroidTextures = {
	"textures/am1.jpg",
	"textures/am2.jpg",
	"textures/am3.jpg",
	"textures/am4.jpg",
	"textures/am5.jpg",
	"textures/am6.jpg",
	"textures/am7.jpg",
	"textures/am8.jpg",
	"textures/am9.jpg",
	"textures/am10.jpg",
	"textures/am11.jpg",
	"textures/am12.jpg",
	"textures/am13.jpg",
	"textures/am14.jpg",
	"textures/am15.jpg"
};

vector<Model*> Asteroid::asteroidModels;