#include "InputManager.h"



InputManager::InputManager(GLFWwindow* win)
{
	glfwSetMouseButtonCallback(win, InputManager::handleMouseClick);
	glfwSetKeyCallback(win, handleKeyPress);
}

void InputManager::handleKeyPress(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	winManagers[window]->keyStates[key] = action;
}

void InputManager::handleMouseClick(GLFWwindow * window, int button, int action, int mods)
{
	winManagers[window]->buttonStates[button] = action;
}

InputManager::~InputManager()
{
}

InputManager * InputManager::getInstance(GLFWwindow* win)
{
	if (winManagers[win] == nullptr) {
		winManagers[win] = new InputManager(win);
	}
	return winManagers[win];
}

map<GLFWwindow*, InputManager*> InputManager::winManagers;