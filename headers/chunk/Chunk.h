#pragma once
#ifndef CHUNK_H
#define CHUNK_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chunk/Block.h>
#include <vector>
#include <rendering/RenderInformation.h>
#include <array>
#include <world/Constants.h>
#include <chunk/terrain-generation/TerrainNoise.h>
#include <rendering/MeshBuffer.h>
#include <chunk/terrain-generation/TreeGeneration.h>

class Chunk
{
public:
	MeshBuffer* solidMesh;
	MeshBuffer* waterMesh;
	glm::vec3 position;
	std::vector<Block*> chunk;
	Chunk(glm::vec3 location);
	~Chunk();
	void createHalfChunk();
	void createSolidChunk();
	void createPerlinNoiseChunk(std::vector<int>& noiseMap, TreeGeneration* tg);
	void createHollowCube();
	void createStairsChunk();
	void changeBlock(glm::ivec3 pos, BlockType block);
	Block* getLocalBlock(int x, int y, int z);
	std::atomic<bool> genFinished;
};
#endif // !CHUNK_H
