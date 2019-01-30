#pragma once
#include <map>
#include <GLFW/glfw3.h>

using namespace std;

class InputManager
{
public:
	~InputManager();

	static InputManager* getInstance(GLFWwindow* win);
	map<int, int> keyStates;
	map<int, int> buttonStates;

private:
	InputManager(GLFWwindow* win);
	static void handleKeyPress(GLFWwindow * window, int key, int scancode, int action, int mods);
	static void handleMouseClick(GLFWwindow * window, int button, int action, int mods);

	static map<GLFWwindow*, InputManager*> winManagers;



};

