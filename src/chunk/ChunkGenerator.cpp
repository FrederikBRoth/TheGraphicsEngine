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
	chunkMap.emplace(key, new IndexedMesh(cb->getChunkMesh(chunk)));
}

void ChunkGenerator::updateChunkMesh(std::string& key, Chunk* chunk)
{
	delete chunkMap[key];
	chunkMap.erase(key);
	chunkMap.insert(std::make_pair(key, new IndexedMesh(cb->getChunkMesh(chunk))));

}

//https://stackoverflow.com/questions/59458264/exception-thrown-read-access-violation-it-was-0xffffffffffffffff






//needs to handle layers