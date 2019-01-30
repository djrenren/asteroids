
#include "Engine.h"


int main() {
	Engine* e = new Engine();

	if (!e->init())
		return -1;

	if (!e->useShaders())
		return -1;

	e->bufferModel();
	e->gameLoop();




}