#include "TextureManager.h"



TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}
GLuint TextureManager::loadTexture(const std::string filename)
{
	const char* file = filename.c_str();
	FREE_IMAGE_FORMAT type = FreeImage_GetFileType(file, 0);
	FIBITMAP* image = FreeImage_Load(type, file);
	FIBITMAP* imagePtr = FreeImage_ConvertTo32Bits(image);

	GLuint texid;
	glGenTextures(1, &texid);
	textures[filename] = texid;

	GLuint width = FreeImage_GetWidth(imagePtr);
	GLuint height = FreeImage_GetHeight(imagePtr);
	BYTE* address = FreeImage_GetBits(imagePtr);

	glBindTexture(GL_TEXTURE_2D, texid);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)address);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	FreeImage_Unload(imagePtr);

	return texid;
}

GLuint TextureManager::getTexture(const std::string name)
{
	if (!textures[name]) {
		return loadTexture(name);
	}
	else return textures[name];
}

GLuint TextureManager::loadCubeMap(const std::string name, std::vector<std::string> files)
{
	GLuint textureID;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for (GLuint i = 0; i < files.size(); i++)
	{
		const char* file = files[i].c_str();
		FREE_IMAGE_FORMAT type = FreeImage_GetFileType(file, 0);
		FIBITMAP* image = FreeImage_Load(type, file);
		FIBITMAP* imagePtr = FreeImage_ConvertTo32Bits(image);
		GLuint width = FreeImage_GetWidth(imagePtr);
		GLuint height = FreeImage_GetHeight(imagePtr);

		BYTE* address = FreeImage_GetBits(imagePtr);

		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
			GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)address
			);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	cubeMaps[name] = textureID;

	return textureID;
}
