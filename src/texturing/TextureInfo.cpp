#include <texturing/TextureInfo.h>

TextureInfo::TextureInfo()
{
	textureInfo.emplace(BlockType::GRASS, glm::vec2(2, 3));
	textureInfo.emplace(BlockType::STONE, glm::vec2(0, 2));
}
