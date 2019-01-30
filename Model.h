#pragma once
#include "Vertex.h"
#include <GL/glew.h>
#include <vector>

using namespace std;
class Model
{
public:

	void render();

	GLuint vertBuf;
	GLuint vertArr;
protected:
	unsigned int vertCount;
};

