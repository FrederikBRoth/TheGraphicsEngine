#include <chunk/ChunkBuilder.h>
#include <iostream>

ChunkBuilder::ChunkBuilder()
{
	this->tcs = std::vector<TextureCoord>(4);
}

ChunkBuilder::ChunkBuilder(TextureInfo* ti)
{
	this->ti = ti;
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
RenderInformation ChunkBuilder::getChunkMesh(Chunk* currentChunk)
{
	RenderInformation ri = RenderInformation();
	short indicesIndex = 0;

	AdjacentBlockPositions directions;

	for (int i = 0; i < CHUNKVOLUME; i++)
	{
		BlockType type = currentChunk->chunk[i]->type;
		if (type != BlockType::AIR) {
			int x = i % CHUNKSIZE_X;
			int y = (i / CHUNKSIZE_Z) % CHUNKSIZE_Y;
			int z = i / (CHUNKSIZE_X * CHUNKSIZE_Y);
			directions.update(x, y, z);
			glm::vec3 pos = glm::vec3(x, y, z);
			BlockFaces* blockFaces = ti->blockInfo[type];
			addFace(&ri, &pos, front, &indicesIndex, &directions.front, frontNormals, currentChunk, blockFaces->front.coords);
			addFace(&ri, &pos, back, &indicesIndex, &directions.back, backNormals, currentChunk, blockFaces->back.coords);
			addFace(&ri, &pos, right, &indicesIndex, &directions.right, rightNormals, currentChunk, blockFaces->right.coords);
			addFace(&ri, &pos, left, &indicesIndex, &directions.left, leftNormals, currentChunk, blockFaces->left.coords);
			addFace(&ri, &pos, top, &indicesIndex, &directions.up, topNormals, currentChunk, blockFaces->up.coords);
			addFace(&ri, &pos, bottom, &indicesIndex, &directions.down, bottomNormals, currentChunk, blockFaces->down.coords);
		}
	}

	return ri;
}




void ChunkBuilder::addFace(RenderInformation* ri, glm::vec3* gridPosition, const std::array<float, 12> &faces, short* indicesIndex, glm::vec3* directions, const glm::vec3 &lightPos, Chunk* currentChunk, std::vector<TextureCoord>& tex)
{
	if (canPlaceFace(directions->x, directions->y, directions->z, currentChunk)) {
		for (int i = 0, faceIndex = 0; i < 4; i++) {
			ri->vertices.push_back((faces[faceIndex++] + currentChunk->position.x + gridPosition->x) * 0.5);
			ri->vertices.push_back((faces[faceIndex++] + currentChunk->position.y + gridPosition->y) * 0.5);
			ri->vertices.push_back((faces[faceIndex++] + currentChunk->position.z + gridPosition->z) * 0.5);
			//adding 3 vectors for normals
			ri->vertices.push_back(lightPos.x);
			ri->vertices.push_back(lightPos.y);
			ri->vertices.push_back(lightPos.z);
			ri->vertices.push_back(tex[i].xCoord);
			ri->vertices.push_back(tex[i].yCoord);

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
	if (x < 0 || x > CHUNKSIZE_X - 1) {
		return true;

	}
	if (y < 0 || y > CHUNKSIZE_Y - 1) {
		return true;

	}
	if (z < 0 || z > CHUNKSIZE_Z - 1) {
		return true;
	}
	//this->currentChunk->chunk[blockCoord.x][blockCoord]
	return false;
}

bool ChunkBuilder::canPlaceFace(int x, int y, int z, Chunk* currentChunk)
{
	if (outOfBounds(x, y, z)) {
		return true;
	}
	if (currentChunk->chunk[getIndex(x, y, z)]->type == BlockType::AIR) {
		return true;
	}
	return false;
}

int ChunkBuilder::getIndex(int x, int y, int z)
{
	return z * CHUNKAREA + y * CHUNKSIZE_X + x;
}
