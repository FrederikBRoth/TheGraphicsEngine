#ifndef CHUNKBUILD_H
#define CHUNKBUILD_H
#include <array>
#include <chunk/Chunk.h>
#include <texturing/TextureCoords.h>
class ChunkBuilder
{
    const std::array<float, 12> frontFace{
    0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1,
    };

    const std::array<float, 12> backFace{
        1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0,
    };

    const std::array<float, 12> leftFace{
        0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0,
    };

    const std::array<float, 12> rightFace{
        1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1,
    };

    const std::array<float, 12> topFace{
        0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0,
    };

    const std::array<float, 12> bottomFace{ 
        0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1 
    };

public:
    Chunk* currentChunk;
    std::vector<TextureCoord> tcs;
    ChunkBuilder(Chunk* currentChunk);
    ChunkBuilder(Chunk* currentChunk, std::vector<TextureCoord> tcs);
    ~ChunkBuilder();
    RenderInformation getChunkMesh();
private:
    void addFaces(RenderInformation* ri, 
        glm::vec3 gridPosition, 
        glm::vec3 chunkPosition, 
        int* indicesIndex);
    void addFace(RenderInformation* ri, 
        glm::vec3 gridPosition, 
        glm::vec3 chunkPosition, 
        std::array<float, 12> faces,
        int* indicesIndex);



};
#endif 
