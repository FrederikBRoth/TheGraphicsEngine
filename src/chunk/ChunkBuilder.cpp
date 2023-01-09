#include <chunk/ChunkBuilder.h>
#include <iostream>

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

struct AdjacentBlockPositions {
	void update(int x, int y, int z)
	{
		up = { x, y + 1, z };
		down = { x, y - 1, z };
		left = { x - 1, y, z };
		right = { x + 1, y, z };
		front = { x, y, z + 1 };
		back = { x, y, z - 1 };
	}

	glm::vec3 up;
	glm::vec3 down;
	glm::vec3 left;
	glm::vec3 right;
	glm::vec3 front;
	glm::vec3 back;
};
RenderInformation* ChunkBuilder::getChunkMesh()
{
	RenderInformation* ri = new RenderInformation();
	int indicesIndex = 0;
	//int chunkVolume = this->currentChunk->CHUNKSIZE_X * this->currentChunk->CHUNKSIZE_Y * this->currentChunk->CHUNKSIZE_Z;
	//for (int i = 0; i < chunkVolume; i++) {
	//	int x = i % this->currentChunk->CHUNKSIZE_X;
	//	int y = (i / this->currentChunk->CHUNKSIZE_Z) % this->currentChunk->CHUNKSIZE_Y;
	//	int z = i / (this->currentChunk->CHUNKSIZE_X * this->currentChunk->CHUNKSIZE_Y);
	//	
	//}

	AdjacentBlockPositions directions;

	for (int i = 0; i < currentChunk->CHUNKVOLUME; i++)
	{
		int x = i % this->currentChunk->CHUNKSIZE_X;
		int y = (i / this->currentChunk->CHUNKSIZE_Z) % this->currentChunk->CHUNKSIZE_Y;
		int z = i / (this->currentChunk->CHUNKSIZE_X * this->currentChunk->CHUNKSIZE_Y);
		directions.update(x, y, z);
		glm::vec3 pos = glm::vec3(x, y, z);
		addFace(ri, &pos, frontFace, &indicesIndex, &directions.front);
		addFace(ri, &pos, backFace, &indicesIndex, &directions.back);
		addFace(ri, &pos, rightFace, &indicesIndex, &directions.right);
		addFace(ri, &pos, leftFace, &indicesIndex, &directions.left);
		addFace(ri, &pos, topFace, &indicesIndex, &directions.up);
		addFace(ri, &pos, bottomFace, &indicesIndex, &directions.down);
		
		
			
		
	}
	return ri;
}



void ChunkBuilder::addFaces(RenderInformation* ri, glm::vec3* gridPosition, int* indicesIndex)
{
	


}

void ChunkBuilder::addFace(RenderInformation* ri, glm::vec3* gridPosition, const std::array<float, 12> &faces, int* indicesIndex, glm::vec3* directions)
{
	if (!outOfBounds(directions->x, directions->y, directions->z) && currentChunk->chunk[currentChunk->getIndex(directions->x, directions->y, directions->z)]->type != BlockType::AIR) {
		for (int i = 0, faceIndex = 0; i < 4; i++) {
			ri->vertices.push_back(faces[faceIndex++] + currentChunk->position.x + gridPosition->x);
			ri->vertices.push_back(faces[faceIndex++] + currentChunk->position.y + gridPosition->y);
			ri->vertices.push_back(faces[faceIndex++] + currentChunk->position.z + gridPosition->z);
			//adding 3 vectors for normals

			ri->vertices.push_back(0.0f);
			ri->vertices.push_back(0.0f);
			ri->vertices.push_back(0.0f);

			ri->vertices.push_back(tcs[i].xCoord);
			ri->vertices.push_back(tcs[i].yCoord);

		}
		ri->indices.push_back(*indicesIndex);
		ri->indices.push_back(*indicesIndex + 1);
		ri->indices.push_back(*indicesIndex + 2);
		ri->indices.push_back(*indicesIndex + 2);
		ri->indices.push_back(*indicesIndex + 3);
		ri->indices.push_back(*indicesIndex);
		*indicesIndex += 4;
	}
	
}

bool ChunkBuilder::outOfBounds(int x, int y, int z)
{
	if (x < 0 || x > currentChunk->CHUNKSIZE_X - 1) {
		return true;

	}
	if (y < 0 || y > currentChunk->CHUNKSIZE_Y - 1) {
		return true;

	}
	if (z < 0 || z > currentChunk->CHUNKSIZE_Z - 1) {
		return true;
	}
	//this->currentChunk->chunk[blockCoord.x][blockCoord]
	return false;
}

bool ChunkBuilder::canPlaceFace(int x, int y, int z)
{
	return false;
}
