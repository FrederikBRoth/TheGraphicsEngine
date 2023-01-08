#include <chunk/ChunkBuilder.h>

ChunkBuilder::ChunkBuilder(Chunk* currentChunk)
{
	this->currentChunk = currentChunk;
	this->tcs = std::vector<TextureCoord>(4);
}

ChunkBuilder::ChunkBuilder(Chunk* currentChunk, std::vector<TextureCoord> tcs)
{
	this->currentChunk = currentChunk;
	this->tcs = tcs;
}

ChunkBuilder::~ChunkBuilder()
{
	delete this->currentChunk;
}

RenderInformation ChunkBuilder::getChunkMesh()
{
	RenderInformation ri = RenderInformation();
	int indicesIndex = 0;

	for (int x = 0; x < this->currentChunk->CHUNKSIZE_X; x++) {
		for (int y = 0; y < this->currentChunk->CHUNKSIZE_Y; y++) {
			for (int z = 0; z < this->currentChunk->CHUNKSIZE_Z; z++) {
				if (this->currentChunk->chunk[x][y][z]->type != BlockType::AIR) {
					addFaces(&ri, { x, y, z }, this->currentChunk->position, &indicesIndex);	
				}
			}
		}
	}
	return ri;
}



void ChunkBuilder::addFaces(RenderInformation* ri, glm::vec3 gridPosition, glm::vec3 chunkPosition, int* indicesIndex)
{
	addFace(ri, gridPosition, chunkPosition, this->frontFace, indicesIndex);
	addFace(ri, gridPosition, chunkPosition, this->backFace, indicesIndex);
	addFace(ri, gridPosition, chunkPosition, this->rightFace, indicesIndex);
	addFace(ri, gridPosition, chunkPosition, this->leftFace, indicesIndex);
	addFace(ri, gridPosition, chunkPosition, this->topFace, indicesIndex);
	addFace(ri, gridPosition, chunkPosition, this->bottomFace, indicesIndex);

}

void ChunkBuilder::addFace(RenderInformation* ri, glm::vec3 gridPosition, glm::vec3 chunkPosition, std::array<float, 12> faces, int* indicesIndex)
{
	for (int i = 0, faceIndex = 0; i < 4; i++) {
		ri->vertices.push_back(faces[faceIndex++] + chunkPosition.x + gridPosition.x);
		ri->vertices.push_back(faces[faceIndex++] + chunkPosition.y + gridPosition.y);
		ri->vertices.push_back(faces[faceIndex++] + chunkPosition.z + gridPosition.z);
		//adding 3 vectors for normals
		for (int j = 0; j < 3; j++) {
			ri->vertices.push_back(0.0f);
		}
		ri->vertices.push_back(this->tcs[i].xCoord);
		ri->vertices.push_back(this->tcs[i].yCoord);

	}
	ri->indices.push_back(*indicesIndex);
	ri->indices.push_back(*indicesIndex + 1);
	ri->indices.push_back(*indicesIndex + 2);
	ri->indices.push_back(*indicesIndex + 2);
	ri->indices.push_back(*indicesIndex + 3);
	ri->indices.push_back(*indicesIndex);
	*indicesIndex += 4;
}
