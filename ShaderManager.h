#pragma once
#include <GL/glew.h>
#include <fstream>
#include <iostream>

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();
	GLuint getProgram() const;
	GLuint loadShaders(const char* vertexFile, const char* fragmentFile);

private:
	GLuint program;
	GLuint loadShader(const char* file, GLenum shaderType);

};

