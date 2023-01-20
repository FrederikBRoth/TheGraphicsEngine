#include <chunk/ChunkGenerator.h>
#include <texturing/TextureInfo.h>

ChunkGenerator::ChunkGenerator(World* world, BlockType type)
{
	this->world = world;
	TextureInfo* ti = new TextureInfo();
	cb = new ChunkBuilder(ti);
}

void ChunkGenerator::createChunkMesh(std::string &key, Chunk* chunk)
{
	chunkMap.insert(std::make_pair(key, cb->getChunkMesh(chunk)));
	std::cout << key << std::endl;
}

void ChunkGenerator::updateChunkMesh(std::string& key, Chunk* chunk)
{
	delete chunkMap[key];
	chunkMap.erase(key);
	chunkMap.insert(std::make_pair(key, cb->getChunkMesh(chunk)));

}

void ChunkGenerator::removeChunkMesh(std::string& key)
{
	delete chunkMap[key];
	chunkMap.erase(key);
}


//https://stackoverflow.com/questions/59458264/exception-thrown-read-access-violation-it-was-0xffffffffffffffff






//needs to handle layers
