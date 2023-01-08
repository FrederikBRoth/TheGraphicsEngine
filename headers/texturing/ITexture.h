#ifndef ITEXTURE_H
#define ITEXTURE_H
#include <string>
#include <iostream>
#include <stb_image.h>
#include <glad/glad.h>
#include <helpers/RootDir.h>
class ITexture {
public:
	unsigned char* textureData;
	std::string texturePath;
	unsigned int ID;
	virtual void loadTexture(int COLORTYPE) = 0;
};
#endif // !ITEXTURE_H
