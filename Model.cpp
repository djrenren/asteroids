#include "Model.h"
#include <glm/glm.hpp>

using namespace glm;



void Model::render()
{
	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);
	glDrawArrays(GL_TRIANGLES, 0, vertCount);
}
