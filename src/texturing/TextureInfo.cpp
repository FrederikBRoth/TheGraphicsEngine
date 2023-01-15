#include <texturing/TextureInfo.h>

TextureInfo::TextureInfo()
{
	texture = new TextureMap(std::string("assets/textures/TextureTable.png"), 16, 16);

	textureInfo.emplace(FaceType::GRASS_TOP, glm::vec2(2, 3));
	textureInfo.emplace(FaceType::GRASS_SIDE, glm::vec2(1, 3));
	textureInfo.emplace(FaceType::STONE, glm::vec2(0, 2));
	textureInfo.emplace(FaceType::DIRT, glm::vec2(0, 3));


	BlockFaces grass = BlockFaces(
		BlockFace(FaceType::GRASS_SIDE, texture, textureInfo),
		BlockFace(FaceType::GRASS_SIDE, texture, textureInfo),
		BlockFace(FaceType::GRASS_TOP, texture, textureInfo),
		BlockFace(FaceType::DIRT, texture, textureInfo),
		BlockFace(FaceType::GRASS_SIDE, texture, textureInfo),
		BlockFace(FaceType::GRASS_SIDE, texture, textureInfo)
	);

	BlockFaces stone = BlockFaces(
		BlockFace(FaceType::STONE, texture, textureInfo),
		BlockFace(FaceType::STONE, texture, textureInfo),
		BlockFace(FaceType::STONE, texture, textureInfo),
		BlockFace(FaceType::STONE, texture, textureInfo),
		BlockFace(FaceType::STONE, texture, textureInfo),
		BlockFace(FaceType::STONE, texture, textureInfo)
	);

	BlockFaces dirt = BlockFaces(
		BlockFace(FaceType::DIRT, texture, textureInfo),
		BlockFace(FaceType::DIRT, texture, textureInfo),
		BlockFace(FaceType::DIRT, texture, textureInfo),
		BlockFace(FaceType::DIRT, texture, textureInfo),
		BlockFace(FaceType::DIRT, texture, textureInfo),
		BlockFace(FaceType::DIRT, texture, textureInfo)
	);


	blockInfo.emplace(BlockType::GRASS, grass);
	blockInfo.emplace(BlockType::STONE, stone);
	blockInfo.emplace(BlockType::DIRT, dirt);

}


BlockFaces::BlockFaces(BlockFace front, BlockFace back, BlockFace up, BlockFace down, BlockFace left, BlockFace right)
{
	this->front = front;
	this->back = back;
	this->up = up;
	this->down = down;
	this->left = left;
	this->right = right;
}

BlockFaces::BlockFaces()
{
	this->front = BlockFace();
	this->back = BlockFace();
	this->up = BlockFace();
	this->down = BlockFace();
	this->left = BlockFace();
	this->right = BlockFace();
}

BlockFace::BlockFace(FaceType face, TextureMap* map, std::unordered_map<FaceType, glm::vec2>& pictureCoord) 
{
	glm::vec2 pictureTexCoord = pictureCoord[face];
	this->coords = map->getTexCoords(pictureTexCoord.x, pictureTexCoord.y);
}

BlockFace::BlockFace()
{
	this->coords = std::vector<TextureCoord>(4);
}
