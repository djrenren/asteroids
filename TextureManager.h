#pragma once
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <FreeImage.h>
class TextureManager
{
public:
	TextureManager();
	~TextureManager();
	GLuint loadTexture(const std::string file);
	GLuint getTexture(const std::string name);
	GLuint loadCubeMap(const std::string name, const std::vector<std::string> files);

private:
	std::map<std::string, GLuint> textures;
	std::map<std::string, GLuint> cubeMaps;
	
};

