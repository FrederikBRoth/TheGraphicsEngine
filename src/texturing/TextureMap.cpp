#include <texturing/TextureMap.h>

void TextureMap::setupTextureCoordinates()
{
	int xCount = this->textureWidth / this->tileWidth;
	int yCount = this->textureHeight / this->tileHeight;
	for (int x = 0; x < xCount; x++) {
		for (int y = 0; y < yCount; y++) {
			TextureCoords tc = TextureCoords();
			float xTexSize = 1.0f / (float)xCount;
			float yTexSize = 1.0f / (float)yCount;
			float xCoord = (float)x * xTexSize;
			float yCoord = (float)y * yTexSize;
			tc.bottomleft = TextureCoord(xCoord, yCoord);
			tc.bottomright = TextureCoord(xCoord + xTexSize, yCoord);
			tc.topright = TextureCoord(xCoord + xTexSize, yCoord + yTexSize);
			tc.topleft = TextureCoord(xCoord, yCoord + yTexSize);
			this->textures[x][y] = tc;
		}
	}
}
TextureMap::TextureMap(std::string filepath, int tileHeight, int tileWidth) : textureHeight(0), textureWidth(0), nrChannels(0)
{
	this->tileHeight = tileHeight;
	this->tileWidth = tileWidth;
	const char* cString = filepath.c_str();
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(cString, &this->textureHeight, &this->textureWidth,
		&nrChannels, 0);
	if (data) {
		this->textureData = data;
		this->textures = std::vector<std::vector<TextureCoords>>(this->textureWidth / this->tileWidth, std::vector<TextureCoords>(this->textureHeight / this->tileHeight));

		setupTextureCoordinates();
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}


}

TextureMap::~TextureMap()
{
	delete this->textureData;
}


void TextureMap::loadTexture(int COLORTYPE)
{
	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	//Sets the texture filtering based on if the texture is upscaled on a larger object or downscaled if on a smaller object
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, COLORTYPE, this->textureWidth, this->textureHeight, 0, COLORTYPE,
		GL_UNSIGNED_BYTE, this->textureData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(this->textureData);
}




void TextureMap::bind()
{
	glBindTexture(GL_TEXTURE_2D, this->ID);
}

std::vector<TextureCoord> TextureMap::getTexCoords(int x, int y)
{
	std::vector<TextureCoord> tcs = std::vector<TextureCoord>();
	tcs.push_back(this->textures[x][y].bottomleft);
	tcs.push_back(this->textures[x][y].bottomright);
	tcs.push_back(this->textures[x][y].topright);
	tcs.push_back(this->textures[x][y].topleft);

	return tcs;
}


