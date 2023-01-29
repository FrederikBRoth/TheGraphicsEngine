#pragma once
#ifndef MESHGEN_H
#define MESHGEN_H
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <world/World.h>
#include <texturing/TextureInfo.h>
struct AdjacentBlockPositions;
struct AdjecentChunkPositions;
struct Meshes {
    RenderInformation solids;
    RenderInformation water;
    RenderInformation sprites;
};

class MeshBuilder
{
    const std::array<float, 12> front{
     0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1
    };

    const std::array<float, 12> back{
        1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0
    };

    const std::array<float, 12> left{
        0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0
    };

    const std::array<float, 12> right{
        1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1
    };

    const std::array<float, 12> top{
        0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0
    };

    const std::array<float, 12> bottom{
        0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1
    };

    const glm::vec3 frontNormals{
        0.0f, 0.0f, 1.0f
    };

    const glm::vec3  backNormals{
        0.0f, 0.0f, -1.0f
    };

    const glm::vec3  leftNormals{
        -1.0f, 0.0f, 0.0f
    };

    const glm::vec3  rightNormals{
        1.0f, 0.0f, 0.0f
    };

    const glm::vec3  topNormals{
        0.0f, 1.0f, 0.0f
    };

    const glm::vec3  bottomNormals{
        0.0f, -1.0f, 0.0f
    };

private:
    void addFace(RenderInformation* ri,
        glm::vec3* gridPosition,
        const std::array<float, 12>& faces,
        short* indicesIndex,
        glm::vec3* directions,
        const glm::vec3& lightPos,
        Chunk* currentChunk,
        std::vector<TextureCoord>& tex,
        VectorXZ* chunkDirection,
        std::unordered_map<VectorXZ, Chunk*>* chunks
    );
    void addBlock(RenderInformation* ri,
        glm::vec3* gridPosition,
        short* indicesIndex,
        AdjacentBlockPositions* directions,
        Chunk* currentChunk,
        BlockFaces* blockFaces,
        AdjecentChunkPositions* chunkDirections,
        std::unordered_map<VectorXZ, Chunk*>* chunks
    );
    bool outOfBounds(int x, int y, int z);
    bool canPlaceFace(int x, int y, int z, glm::vec3* pos, Chunk* currentChunk, std::unordered_map<VectorXZ, Chunk*>* chunks, VectorXZ* borderChunkLocation);
    TextureInfo* ti;
public:
	World* world;
	std::unordered_map<VectorXZ, MeshBuffer*> chunkMap;
	MeshBuilder(World* world);
	void createChunkMesh(VectorXZ& key, std::unordered_map<VectorXZ, Chunk*>* chunks);
	void updateChunkMesh(VectorXZ& key, std::unordered_map<VectorXZ, Chunk*>* chunks);
	void removeChunkMesh(VectorXZ& key);
    Meshes getChunkMesh(VectorXZ& key, std::unordered_map<VectorXZ, Chunk*>* chunks);

};
#endif // !CHUNKGEN_H