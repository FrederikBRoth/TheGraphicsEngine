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
	if (!chunkMap.count(key)) {
		MeshBuffer* buffer = chunk->mesh;
		buffer->loadMesh(cb->getChunkMesh(chunk), MeshConfig(8, true, true, MeshShape::TRIANGLE));
		chunkMap.insert(std::make_pair(key, buffer));
	}

}

void ChunkGenerator::updateChunkMesh(std::string& key, Chunk* chunk)
{
	MeshBuffer* buffer = chunk->mesh;
	buffer->loadMesh(cb->getChunkMesh(chunk), MeshConfig(8, true, true, MeshShape::TRIANGLE));
	chunkMap.erase(key);
	chunkMap.insert(std::make_pair(key, buffer));

}

void ChunkGenerator::removeChunkMesh(std::string& key)
{
	chunkMap.erase(key);
}


//https://stackoverflow.com/questions/59458264/exception-thrown-read-access-violation-it-was-0xffffffffffffffff






//needs to handle layers
