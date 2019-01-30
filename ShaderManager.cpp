#include "ShaderManager.h"
#include "TextureManager.h"

using namespace std;

ShaderManager::ShaderManager()
{
}


ShaderManager::~ShaderManager()
{
}



GLuint ShaderManager::loadShaders(const char* vertexFile, const char* fragmentFile)
{
	GLuint vertShader = loadShader(vertexFile, GL_VERTEX_SHADER);
	if (vertShader == 0) {
		return 0;
	}
	GLuint fragShader = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	if (fragShader == 0) {
		return 0;
	}

	GLuint shaderProg = glCreateProgram();
	glAttachShader(shaderProg, vertShader);
	glAttachShader(shaderProg, fragShader);

	glLinkProgram(shaderProg);

	GLint linkStatus = 0;
	glGetProgramiv(shaderProg, GL_LINK_STATUS, &linkStatus);

	if (linkStatus != 0) {
		return shaderProg;
	}

	GLint logLength = 0;
	glGetProgramiv(shaderProg, GL_INFO_LOG_LENGTH, &logLength);

	GLchar* log = new GLchar[logLength];

	glGetProgramInfoLog(program, logLength, 0, log);

	cout << "Shader linking error: " << endl;
	cout << log << endl;

	glDeleteProgram(shaderProg);
	delete[] log;
	return 0;


	return false;
}

GLuint ShaderManager::loadShader(const char* file, GLenum shaderType)
{
	// Read file
	ifstream inFile(file, ios::binary);
	if (!inFile.is_open()) {
		cout << "Failed to read file '" << file << "'" << endl;
		return 0;
	}
	inFile.seekg(0, ios::end);
	int length = (int)inFile.tellg();
	
	inFile.seekg(0, ios::beg);

	char* fileContents = new char[length + 1];

	inFile.read(fileContents, length);
	fileContents[length] = 0;

	inFile.close();

	// Load shader
	GLuint shaderIdx = glCreateShader(shaderType);
	glShaderSource(shaderIdx, 1, &fileContents, 0);

	glCompileShader(shaderIdx);

	delete[] fileContents;

	GLint compilationStatus = 0;
	glGetShaderiv(shaderIdx, GL_COMPILE_STATUS, &compilationStatus);

	if (compilationStatus != 0) {
		return shaderIdx;
	}
	
	// Log Compilation Errors
	GLint logLength = 0;
	glGetShaderiv(shaderIdx, GL_INFO_LOG_LENGTH, &logLength);

	GLchar* log = new GLchar[logLength];
	glGetShaderInfoLog(shaderIdx, logLength, 0, log);

	cout << "Shader compilation error: " << endl;
	cout << log << endl;

	glDeleteShader(shaderIdx);
	delete[] log;
	
	return 0;
}
