#include <chunk/Chunk.h>


Chunk::Chunk(glm::vec3 position)
{
	this->position = position;
	this->chunk = std::vector<Block*>(CHUNKVOLUME);
	mesh = new MeshBuffer();
}


Chunk::~Chunk()
{
	for (auto block : chunk) {
		delete block;
	}
	this->chunk.clear();
	this->chunk.shrink_to_fit();
	delete this->mesh;
}

void Chunk::createHalfChunk()
{
	for (int i = 0; i < CHUNKVOLUME; i++) {
		int x = i % CHUNKSIZE_X;
		int y = (i / CHUNKSIZE_Z) % CHUNKSIZE_Y;
		int z = i / (CHUNKSIZE_X * CHUNKSIZE_Y);
		if (y < CHUNKSIZE_Y/2) {
			chunk[i] = new Block(BlockType::GRASS);
		}
		else {
			chunk[i] = new Block(BlockType::AIR);
		}
	}
}




void Chunk::createSolidChunk()
{
	for (int x = 0; x < CHUNKVOLUME; x++) {
		this->chunk[x] = new Block(BlockType::GRASS);	
	}
}

void Chunk::createPerlinNoiseChunk(std::vector<int>& noiseMap)
{
	int mid = CHUNKSIZE_Y / 2;
	for (int i = 0; i < CHUNKVOLUME; i++) {
		int x = i % CHUNKSIZE_X;
		int y = (i / CHUNKSIZE_Z) % CHUNKSIZE_Y;
		int z = i / (CHUNKSIZE_X * CHUNKSIZE_Y);
		int id = z * CHUNKSIZE_X + x;
		int offset = noiseMap[id];

		if (y < mid - offset) {
			if (y == (mid - offset)-1) {
				chunk[i] = new Block(BlockType::GRASS);
			}
			else if(y < mid - offset && y > mid - offset - 3){
				chunk[i] = new Block(BlockType::DIRT);
			}
			else {
				chunk[i] = new Block(BlockType::STONE);
			}

		}
		else {
			if (y < WATER_LEVEL) {
				chunk[i] = new Block(BlockType::WATER);
			}
			else {
				chunk[i] = new Block(BlockType::AIR);

			}
		}
	}
}

void Chunk::createHollowCube()
{
	int min = 3;
	int max = CHUNKSIZE_X - 3;
	for (int i = 0; i < CHUNKVOLUME; i++) {
		int x = i % CHUNKSIZE_X;
		int y = (i / CHUNKSIZE_Z) % CHUNKSIZE_Y;
		int z = i / (CHUNKSIZE_X * CHUNKSIZE_Y);
		if (x > min && x < max && y > min && y < max && z > min && z < max) {
			chunk[i] = new Block(BlockType::AIR);
		}
		else {
			chunk[i] = new Block(BlockType::GRASS);

		}
	}
}

void Chunk::createStairsChunk()
{

	for (int i = 0; i < CHUNKVOLUME; i++) {
		int x = i % CHUNKSIZE_X;
		int y = (i / CHUNKSIZE_Z) % CHUNKSIZE_Y;
		int z = i / (CHUNKSIZE_X * CHUNKSIZE_Y);
		if (x == y) {
			chunk[i] = new Block(BlockType::GRASS);
		}
		else {
			chunk[i] = new Block(BlockType::AIR);
		}
	}
}









