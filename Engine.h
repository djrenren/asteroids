#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_SWIZZLE

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <FreeImage.h>
#include <vector>
#include "ShaderManager.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Camera.h"
#include <memory>
#include "Skybox.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Asteroid.h"

#pragma once
class Engine
{
private:
	GLFWwindow* GLFWwindowPtr;
	GLuint worldTransform;
	unsigned int vertCount;
	ShaderManager sm;
	InputManager* input;
	Camera camera;
	GLuint objectShader;
	GLuint skyboxShader;
	Skybox* skybox;

	milliseconds lastFired;
	Model* shotModel;
	vector<Asteroid*> asteroids;

	vector<GameObject*> shots;
	void cleanAsteroids();
	void collide();
	void genAsteroids(int ct, int minDist, int maxDist);
	void shoot();


public:
	Engine();

	bool init();
	bool bufferModel();
	bool gameLoop();
	bool useShaders();
	TextureManager tm;


	~Engine();

};

