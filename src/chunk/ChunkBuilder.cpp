#include <chunk/ChunkBuilder.h>

ChunkBuilder::ChunkBuilder(Chunk* currentChunk)
{
	this->currentChunk = currentChunk;
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
		//Temp to get each triangle to 8 vectors. Should be normal vectors for light and texture coordinates
		for (int j = 0; j < 5; j++) {
			ri->vertices.push_back(0.0f);
		}
	}
	ri->indices.push_back(*indicesIndex);
	ri->indices.push_back(*indicesIndex + 1);
	ri->indices.push_back(*indicesIndex + 2);
	ri->indices.push_back(*indicesIndex + 2);
	ri->indices.push_back(*indicesIndex + 3);
	ri->indices.push_back(*indicesIndex);
	*indicesIndex += 4;
}
