#include <chunk/ChunkGenerator.h>
#include <texturing/TextureInfo.h>

ChunkGenerator::ChunkGenerator(World* world, BlockType type)
{
	this->world = world;
	TextureInfo ti = TextureInfo();
	glm::vec2 texCoord = ti.textureInfo[type];
	tm = new TextureMap(std::string("assets/textures/TextureTable.png"), 16, 16);
	cb = new ChunkBuilder(tm->getTexCoords(texCoord.x, texCoord.y));
}



void ChunkGenerator::createChunkMesh(std::string &key, Chunk* chunk)
{
	chunkMap.emplace(key, new IndexedMesh(cb->getChunkMesh(chunk)));
}

void ChunkGenerator::updateChunkMesh(std::string& key, Chunk* chunk)
{
	delete chunkMap[key];
	chunkMap.erase(key);
	test = cb->getChunkMesh(chunk);

	chunkMap.insert(std::make_pair(key, new IndexedMesh(test)));

}

//https://stackoverflow.com/questions/59458264/exception-thrown-read-access-violation-it-was-0xffffffffffffffff






//needs to handle layers
