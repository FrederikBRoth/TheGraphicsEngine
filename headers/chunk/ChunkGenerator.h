#pragma once
#ifndef CHUNKGEN_H
#define CHUNKGEN_H
#endif // !CHUNKGEN_H
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <world/World.h>
class ChunkGenerator
{
public:
	World* world;
	ChunkBuilder* cb;
	std::unordered_map<std::string, IndexedMesh*> chunkMap;
	ChunkGenerator(World* world, BlockType type);
	void createChunkMesh(std::string& key, Chunk* chunk);
	void updateChunkMesh(std::string& key, Chunk* chunk);
};
