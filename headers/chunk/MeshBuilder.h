#pragma once
#ifndef MESHGEN_H
#define MESHGEN_H
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <world/World.h>
class MeshBuilder
{
public:

	World* world;
	ChunkBuilder* cb;
	std::unordered_map<std::string, MeshBuffer*> chunkMap;
	MeshBuilder(World* world, BlockType type);
	void createChunkMesh(std::string& key, Chunk* chunk);
	void updateChunkMesh(std::string& key, Chunk* chunk);
	void removeChunkMesh(std::string& key);
};
#endif // !CHUNKGEN_H
