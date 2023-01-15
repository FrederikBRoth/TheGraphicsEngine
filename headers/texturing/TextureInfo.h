
#ifndef TEXTUREINFO_H
#define TEXTUREINFO_H
#include <unordered_map>
#include <chunk/Block.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <texturing/TextureMap.h>
struct BlockFace {
	std::vector<TextureCoord> coords;
	BlockFace(FaceType face, TextureMap* map, std::unordered_map<FaceType, glm::vec2>& xys);
	BlockFace();
};
struct BlockFaces {
	BlockFace front;
	BlockFace back;
	BlockFace up;
	BlockFace down;
	BlockFace left;
	BlockFace right;
	BlockFaces(BlockFace front, BlockFace back, BlockFace up, BlockFace down, BlockFace left, BlockFace right);
	BlockFaces();
};
class TextureInfo
{
public:
	TextureMap* texture;
	std::unordered_map<FaceType, glm::vec2> textureInfo;
	std::unordered_map<BlockType, BlockFaces> blockInfo;
	TextureInfo();
};
#endif // !TEXTUREINFO_H
