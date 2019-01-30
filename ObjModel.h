#pragma once
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Model.h"
#include <fstream>
#include <sstream>

using namespace std;
using namespace glm;

struct VertInd {
	unsigned int locInd, uvInd, normInd;
};

class ObjModel : public Model
{
public:
	ObjModel(string filename);
	~ObjModel();


	struct Vertex {
		vec3 location;
		vec2 uv;
		vec3 normal;
	};
};

