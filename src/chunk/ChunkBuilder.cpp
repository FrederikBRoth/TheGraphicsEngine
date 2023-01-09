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

	AdjacentBlockPositions directions;

	for (int i = 0; i < currentChunk->CHUNKVOLUME; i++)
	{
		if (currentChunk->chunk[i]->type != BlockType::AIR) {
			int x = i % this->currentChunk->CHUNKSIZE_X;
			int y = (i / this->currentChunk->CHUNKSIZE_Z) % this->currentChunk->CHUNKSIZE_Y;
			int z = i / (this->currentChunk->CHUNKSIZE_X * this->currentChunk->CHUNKSIZE_Y);
			directions.update(x, y, z);
			glm::vec3 pos = glm::vec3(x, y, z);
			addFace(ri, &pos, front, &indicesIndex, &directions.front, frontNormals);
			addFace(ri, &pos, back, &indicesIndex, &directions.back, backNormals);
			addFace(ri, &pos, right, &indicesIndex, &directions.right, rightNormals);
			addFace(ri, &pos, left, &indicesIndex, &directions.left, leftNormals);
			addFace(ri, &pos, top, &indicesIndex, &directions.up, topNormals);
			addFace(ri, &pos, bottom, &indicesIndex, &directions.down, bottomNormals);
		}
	}
	return ri;
}




void ChunkBuilder::addFace(RenderInformation* ri, glm::vec3* gridPosition, const std::array<float, 12> &faces, int* indicesIndex, glm::vec3* directions, const glm::vec3 &lightPos)
{
	if (canPlaceFace(directions->x, directions->y, directions->z)) {
		for (int i = 0, faceIndex = 0; i < 4; i++) {
			ri->vertices.push_back(faces[faceIndex++] + currentChunk->position.x + gridPosition->x);
			ri->vertices.push_back(faces[faceIndex++] + currentChunk->position.y + gridPosition->y);
			ri->vertices.push_back(faces[faceIndex++] + currentChunk->position.z + gridPosition->z);
			//adding 3 vectors for normals
			ri->vertices.push_back(lightPos.x);
			ri->vertices.push_back(lightPos.y);
			ri->vertices.push_back(lightPos.z);
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
	if (outOfBounds(x, y, z)) {
		return true;
	}
	if (currentChunk->chunk[currentChunk->getIndex(x, y, z)]->type == BlockType::AIR) {
		return true;
	}
	return false;
}
