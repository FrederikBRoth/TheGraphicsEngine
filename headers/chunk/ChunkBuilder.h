#ifndef CHUNKBUILD_H
#define CHUNKBUILD_H
#include <array>
#include <chunk/Chunk.h>
#include <texturing/TextureCoords.h>
class ChunkBuilder
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

public:
    std::vector<TextureCoord> tcs;
    ChunkBuilder();
    ChunkBuilder(std::vector<TextureCoord> tcs);
    RenderInformation* getChunkMesh(Chunk* currentChunk);
private:

    void addFace(RenderInformation* ri,
        glm::vec3* gridPosition,
        const std::array<float, 12> &faces,
        short* indicesIndex, 
        glm::vec3* direction, 
        const glm::vec3 &lightPos,
        Chunk* currentChunk);
    bool outOfBounds(int x, int y, int z);
    bool canPlaceFace(int x, int y, int z, Chunk* currentChunk);
    int getIndex(int x, int y, int z);

};
#endif 
