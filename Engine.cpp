#include "Engine.h"
#include "ObjModel.h"

using namespace glm;




Engine::Engine()
{
	sm = ShaderManager();
	tm = TextureManager();
}

bool Engine::init()
{
	if (glfwInit() == GL_FALSE)
		return false;

	this->GLFWwindowPtr = glfwCreateWindow(800, 600, "John Renner DSA1 Engine", NULL, NULL);

	if (this->GLFWwindowPtr == nullptr) {
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(GLFWwindowPtr);


	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return false;
	}

	this->input = InputManager::getInstance(this->GLFWwindowPtr);

	srand(time(NULL));


	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(GLFWwindowPtr, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);


	return true;
}


bool Engine::bufferModel()
{
	shotModel = new ObjModel("models/box.obj");
	
	skybox = new Skybox(100, tm.loadCubeMap("skybox", {
		"textures/skybox/space_left2.png",
		"textures/skybox/space_right1.png",
		"textures/skybox/space_top3.png",
		"textures/skybox/space_bottom4.png",
		"textures/skybox/space_back6.png",
		"textures/skybox/space_front5.png",
	}));


	Asteroid::bufferModels();
	camera = Camera(
		Transform{
			{0,0,1},
			{0,0,0},
			{1,1,1}
	},

		1.f,
		.01f,
		1000.f,
		.005f
		);


	return true;
}

bool Engine::gameLoop() {

	
	bool mouseDown = false;
	milliseconds time = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		) - milliseconds(10);

	milliseconds start = time;
	float MAX_SPEED = 1;

	while (!glfwWindowShouldClose(this->GLFWwindowPtr)) {
		milliseconds new_time = duration_cast< milliseconds >(
			system_clock::now().time_since_epoch()
		);

	
		milliseconds delta = new_time - time;

		glfwPollEvents();


		glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		int width;
		int height;
		double x, y;
		glfwGetFramebufferSize(GLFWwindowPtr, &width, &height);
		
		glViewport(0, 0, width, height);

		//glfwGetWindowSize(GLFWwindowPtr, &width, &height);

		glfwGetCursorPos(GLFWwindowPtr,&x, &y);

		camera.update(delta, width, height, x, y);
		if (length2(camera.rigidBody.velocity) > MAX_SPEED * MAX_SPEED) {
			camera.rigidBody.velocity = normalize(camera.rigidBody.velocity) * MAX_SPEED;
		}
		glDepthMask(GL_FALSE);
		glUseProgram(skyboxShader);
		camera.render();
		skybox->render();
		skybox->transform.location = camera.transform.location;
		glDepthMask(GL_TRUE);
		glUseProgram(objectShader);

		glfwSetCursorPos(GLFWwindowPtr, width * .5f, height * .5f);
		camera.render();

		float force = .2;

		if (input->keyStates[GLFW_KEY_D]) {
			camera.rigidBody.force += camera.rotMat * vec3(force, 0, 0);
		}
		if (input->keyStates[GLFW_KEY_W]) {
			camera.rigidBody.force += camera.rotMat * vec3(0, 0, -force);
		}
		if (input->keyStates[GLFW_KEY_A]) {
			camera.rigidBody.force += camera.rotMat * vec3(-force, 0, 0);
		}
		if (input->keyStates[GLFW_KEY_S]) {
			camera.rigidBody.force += camera.rotMat * vec3(0, 0, force);
		}
		
		if (input->buttonStates[GLFW_MOUSE_BUTTON_1] && (time - lastFired) > milliseconds(200)) {
			lastFired = time;
			shoot();
		}

		//objects[1]->textureFile = objects[1]->collidesWith(*objects[0]) ? objects[0]->textureFile : "textures/plaid.jpg";
		
		for (auto& o : asteroids) {
			o->update(delta);
			o->render(&tm);
		}

		for (auto& o : shots) {
			o->update(delta);
			o->render(&tm);
		}
		collide();

		time = new_time;
		
		glfwSwapBuffers(GLFWwindowPtr);

		if (input->keyStates[GLFW_KEY_ESCAPE]) {
			glfwSetWindowShouldClose(this->GLFWwindowPtr, 1);
		}

		cleanAsteroids();

		if (time - start > milliseconds(5000)) {
			genAsteroids(20u - asteroids.size(), 500, 1000);
		}
		else {
			genAsteroids(10u - asteroids.size(), 500, 1000);

		}
	}
	glfwTerminate();
	
	return true;
}

bool Engine::useShaders()
{
	skyboxShader = sm.loadShaders("shaders/skyboxVShader.glsl", "shaders/skyboxFShader.glsl");

	objectShader = sm.loadShaders("shaders/vShader.glsl", "shaders/fShader.glsl");

	if (objectShader == 0 || skyboxShader == 0) {
		return false;
	}
	glUseProgram(objectShader);

}

void Engine::cleanAsteroids() {
	for (unsigned int i = 0; i < asteroids.size(); i++) {
		if (length2(asteroids[i]->transform->location - camera.transform.location) > 800 * 800) {
			free(asteroids[i]);
			asteroids.erase(asteroids.begin() + i);
			i -= 1;
		}
	}

	for (unsigned int i = 0; i < shots.size(); i++) {
		if (length2(shots[i]->transform->location - camera.transform.location) > 800 * 800) {
			free(shots[i]);
			shots.erase(shots.begin() + i);
			i -= 1;
		}
	}
}

void Engine::genAsteroids(int ct, int minDist, int maxDist) {
	for (; ct--;) {
		asteroids.push_back(Asteroid::random(camera.transform.location, 50, minDist, maxDist));
	}
}

void Engine::shoot()
{
	shots.push_back(new GameObject(
		make_shared<Transform>(Transform{
			{camera.transform.location.x, camera.transform.location.y, camera.transform.location.z},
			{ camera.transform.rotation.x, camera.transform.rotation.y, camera.transform.rotation.z },
			{1,1,1}
		}),
		shotModel,
		"textures/white.png",
		RigidBody{ camera.rotMat * vec3(0,0,-6), {0,0,0}, 1 },
		AABB
	));
}

void Engine::collide() {
	shotsLabel:
	for (int i = 0; i < shots.size(); i++) {
		for (int j = 0; j < asteroids.size(); j++) {
			if (shots[i]->collidesWith(*asteroids[j])) {
				free(shots[i]);
				free(asteroids[j]);
				shots.erase(shots.begin() + i--);
				asteroids.erase(asteroids.begin() + j--);
				goto shotsLabel;
			}
		}
	}
}


Engine::~Engine()
{
}
