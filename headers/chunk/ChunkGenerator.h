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
	std::unordered_map<std::string, IndexedMesh*> chunkMap;
	ChunkGenerator(World* world);
	bool chunkExists(int x, int z);
	void createChunk();
	void createChunk(int x, int z);

	void update();
	std::string makeMapKey(int x, int z);
	void infiniteTest();

};
