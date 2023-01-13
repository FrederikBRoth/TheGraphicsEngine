
#ifndef TEXTUREINFO_H
#define TEXTUREINFO_H
#include <unordered_map>
#include <chunk/Block.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class TextureInfo
{
public:
	std::unordered_map<BlockType, glm::vec2> textureInfo;
	TextureInfo();
};
#endif // !TEXTUREINFO_H
