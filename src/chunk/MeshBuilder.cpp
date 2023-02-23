#include <chunk/MeshBuilder.h>
#include <texturing/TextureInfo.h>
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

struct AdjecentChunkPositions {
	void update(int x, int z)
	{
		left = tge::getKey(x - 1, z);
		right = tge::getKey(x + 1, z);
		front = tge::getKey(x, z + 1);
		back = tge::getKey(x, z - 1);
	}
	VectorXZ left;
	VectorXZ right;
	VectorXZ front;
	VectorXZ back;
};

MeshBuilder::MeshBuilder(World* world)
{
	this->world = world;
	ti = new TextureInfo();
}

void MeshBuilder::createChunkMesh(VectorXZ& key, std::unordered_map<VectorXZ, Chunk*>*chunks)
{
	if (!chunkMap.count(key)) {
		//auto start = std::chrono::high_resolution_clock::now();

		MeshBuffer* solidBuffer = chunks->at(key)->solidMesh;
		MeshBuffer* waterBuffer = chunks->at(key)->waterMesh;
		Meshes meshes = getChunkMesh(key, chunks);
		solidBuffer->loadMesh(meshes.solids, MeshConfig(8, true, true, MeshShape::TRIANGLE));
		waterBuffer->loadMesh(meshes.water, MeshConfig(8, true, true, MeshShape::TRIANGLE));
		chunkMap.insert(std::make_pair(key, solidBuffer));
		waterMap.insert(std::make_pair(key, waterBuffer));
		//auto stop = std::chrono::high_resolution_clock::now();
		//auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		//std::cout << "Runtime: " << duration.count() << " microseconds" << std::endl;
	}

}

void MeshBuilder::updateChunkMesh(VectorXZ& key, std::unordered_map<VectorXZ, Chunk*>* chunks)
{
	MeshBuffer* solidBuffer = chunks->at(key)->solidMesh;
	MeshBuffer* waterBuffer = chunks->at(key)->waterMesh;
	Meshes meshes = getChunkMesh(key, chunks);
	solidBuffer->loadMesh(meshes.solids, MeshConfig(8, true, true, MeshShape::TRIANGLE));
	waterBuffer->loadMesh(meshes.water, MeshConfig(8, true, true, MeshShape::TRIANGLE));
	chunkMap.erase(key);
	chunkMap.insert(std::make_pair(key, solidBuffer));
	waterMap.erase(key);
	waterMap.insert(std::make_pair(key, waterBuffer));
}

void MeshBuilder::removeChunkMesh(VectorXZ& key)
{
	chunkMap.erase(key);
	waterMap.erase(key);

}

bool MeshBuilder::outOfBounds(int x, int y, int z)
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
	return false;
}

bool MeshBuilder::canPlaceFace(int x, int y, int z, glm::vec3* pos, Chunk* currentChunk, std::unordered_map<VectorXZ, Chunk*>* chunks, VectorXZ* borderChunkLocation)
{

	BlockType currentType = currentChunk->chunk[tge::getIndex(pos->x, pos->y, pos->z)]->type;

	if (outOfBounds(x, y, z)) {
		if (borderChunkLocation != nullptr && chunks->count(*borderChunkLocation)) {
			glm::ivec3 newPos = { tge::modulus(x, 16), pos->y, tge::modulus(z, 16) };
			BlockType type = chunks->at(*borderChunkLocation)->chunk[tge::getIndex(newPos.x, newPos.y, newPos.z)]->type;
			if (currentType == BlockType::WATER) {
				if (type == BlockType::AIR) {
					return true;
				}
			}
			else {
				if (type == BlockType::AIR || type == BlockType::WATER) {
					return true;
				}
			}
			return false;
		}
		return false;
	}
	BlockType nearbyType = currentChunk->chunk[tge::getIndex(x, y, z)]->type;
	if (currentType == BlockType::WATER) {
		if (nearbyType == BlockType::AIR) {
			return true;
		}
	}
	else {
		if (nearbyType == BlockType::AIR || nearbyType == BlockType::WATER) {
			return true;
		}
	}
	return false;
}

Meshes MeshBuilder::getChunkMesh(VectorXZ& key, std::unordered_map<VectorXZ, Chunk*>* chunks)
{
	Meshes meshes = Meshes();
	short solidIndicesIndex = 0;
	short waterIndicesIndex = 0;

	AdjacentBlockPositions directions;
	AdjecentChunkPositions chunkDirections;
	chunkDirections.update(key.x, key.z);
	for (int i = 0; i < CHUNKVOLUME; i++)
	{
		BlockType type = chunks->at(key)->chunk[i]->type;
		if (type != BlockType::AIR) {
			int x = i % CHUNKSIZE_X;
			int y = (i / CHUNKSIZE_Z) % CHUNKSIZE_Y;
			int z = i / (CHUNKSIZE_X * CHUNKSIZE_Y);
			directions.update(x, y, z);
			glm::vec3 pos = glm::vec3(x, y, z);
			BlockFaces* blockFaces = ti->blockInfo[type];
			if (type == BlockType::WATER) {
				addBlock(&meshes.water, &pos, &waterIndicesIndex, &directions, chunks->at(key), blockFaces, &chunkDirections, chunks);
			}
			else {
				addBlock(&meshes.solids, &pos, &solidIndicesIndex, &directions, chunks->at(key), blockFaces, &chunkDirections, chunks);
			}
		}
	}

	return meshes;
}


void MeshBuilder::addBlock(
	RenderInformation* ri, 
	glm::vec3* gridPosition, 
	short* indicesIndex, 
	AdjacentBlockPositions* directions, 
	Chunk* currentChunk, 
	BlockFaces* blockFaces, 
	AdjecentChunkPositions* chunkDirections,
	std::unordered_map<VectorXZ, Chunk*>* chunks
)
{
	addFace(ri, gridPosition, front, indicesIndex, &directions->front, frontNormals, currentChunk, blockFaces->front.coords, &chunkDirections->front, chunks);
	addFace(ri, gridPosition, back, indicesIndex, &directions->back, backNormals, currentChunk, blockFaces->back.coords, &chunkDirections->back, chunks);
	addFace(ri, gridPosition, right, indicesIndex, &directions->right, rightNormals, currentChunk, blockFaces->right.coords, &chunkDirections->right, chunks);
	addFace(ri, gridPosition, left, indicesIndex, &directions->left, leftNormals, currentChunk, blockFaces->left.coords, &chunkDirections->left, chunks);
	addFace(ri, gridPosition, top, indicesIndex, &directions->up, topNormals, currentChunk, blockFaces->up.coords, nullptr, chunks);
	addFace(ri, gridPosition, bottom, indicesIndex, &directions->down, bottomNormals, currentChunk, blockFaces->down.coords, nullptr, chunks);
}


void MeshBuilder::addFace(
	RenderInformation* ri, 
	glm::vec3* gridPosition, 
	const std::array<float, 12>& faces,
	short* indicesIndex, 
	glm::vec3* directions, 
	const glm::vec3& lightPos, 
	Chunk* currentChunk, 
	std::vector<TextureCoord>& tex, 
	VectorXZ* chunkDirection,
	std::unordered_map<VectorXZ, Chunk*>* chunks
)
{
	if (canPlaceFace(directions->x, directions->y, directions->z, gridPosition, currentChunk, chunks, chunkDirection)) {
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

void MeshBuilder::addSingleBlock(
	RenderInformation* ri,
	BlockFaces* blockFaces,
	glm::vec3* position
)
{
	short indicesIndex = 0;
	addSingleFace(ri, front, indicesIndex, frontNormals, blockFaces->front.coords, position);
	addSingleFace(ri, back, indicesIndex, backNormals, blockFaces->back.coords, position);
	addSingleFace(ri, right, indicesIndex, rightNormals, blockFaces->right.coords, position);
	addSingleFace(ri, left, indicesIndex,  leftNormals,  blockFaces->left.coords, position);
	addSingleFace(ri, top, indicesIndex, topNormals, blockFaces->up.coords, position);
	addSingleFace(ri, bottom, indicesIndex, bottomNormals, blockFaces->down.coords, position);
}


void MeshBuilder::addSingleFace(
	RenderInformation* ri,
	const std::array<float, 12>& faces,
	short& indicesIndex,
	const glm::vec3& lightPos,
	std::vector<TextureCoord>& tex,
	glm::vec3* position
)
{

	for (int i = 0, faceIndex = 0; i < 4; i++) {
		ri->vertices.push_back((faces[faceIndex++] + position->x) * 0.5);
		ri->vertices.push_back((faces[faceIndex++] + position->y) * 0.5);
		ri->vertices.push_back((faces[faceIndex++] + position->z) * 0.5);
		//adding 3 vectors for normals
		ri->vertices.push_back(lightPos.x);
		ri->vertices.push_back(lightPos.y);
		ri->vertices.push_back(lightPos.z);
		ri->vertices.push_back(tex[i].xCoord);
		ri->vertices.push_back(tex[i].yCoord);
	}
	ri->indices.push_back(indicesIndex);
	ri->indices.push_back(indicesIndex + 1);
	ri->indices.push_back(indicesIndex + 2);
	ri->indices.push_back(indicesIndex + 2);
	ri->indices.push_back(indicesIndex + 3);
	ri->indices.push_back(indicesIndex);
	indicesIndex += 4;
	
}


//https://stackoverflow.com/questions/59458264/exception-thrown-read-access-violation-it-was-0xffffffffffffffff






//needs to handle layers
