#ifndef TEXTUREMAP_H
#define TEXTUREMAP_H
#include <texturing/ITexture.h>
#include <texturing/TextureCoords.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class TextureMap : public ITexture
{
private:
	int tileWidth;
	int tileHeight;
	int textureWidth;
	int textureHeight;
	int nrChannels;
	void setupTextureCoordinates();
public:
	std::vector<std::vector<TextureCoords>> textures;
	TextureMap(std::string filepath, int tileHeight, int tileWidth);
	~TextureMap();
	// Inherited via ITexture
	virtual void loadTexture(int COLORTYPE) override;
	void bind();
	std::vector<TextureCoord> getTexCoords(int x, int y);
};
#endif // !
