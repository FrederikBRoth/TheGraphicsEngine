#include <chunk/Chunk.h>

Chunk::Chunk(glm::vec3 position) : CHUNKSIZE_X(16), CHUNKSIZE_Y(16), CHUNKSIZE_Z(16)
{
	this->position = position;
	this->chunk = std::vector<Block*>(CHUNKVOLUME);
}
Chunk::Chunk(glm::vec3 position, int x, int y, int z) : CHUNKSIZE_X(x), CHUNKSIZE_Y(y), CHUNKSIZE_Z(z)
{
	this->position = position;
	this->chunk = std::vector<Block*>(CHUNKVOLUME);
}


Chunk::~Chunk()
{
	for (auto block : chunk) {
		delete block;
	}
	this->chunk.clear();
	this->chunk.shrink_to_fit();
}




void Chunk::createSolidChunk()
{
	for (int x = 0; x < CHUNKVOLUME; x++) {
		this->chunk[x] = new Block(BlockType::GRASS);	
	}
}

void Chunk::CreateHollowCube()
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
	/*for (int x = 0; x < CHUNKSIZE_X; x++) {
		for (int y = 0; y < CHUNKSIZE_Y; y++) {
			for (int z = 0; z < CHUNKSIZE_Z; z++) {
				if (x == y) {
					this->chunk[x][y][z] = new Block(BlockType::GRASS);
				}
				else {
					this->chunk[x][y][z] = new Block(BlockType::AIR);
				}
			}
		}
	}*/
}

int Chunk::getIndex(int x, int y, int z)
{
	return z * CHUNKAREA + y * CHUNKSIZE_X + x;
}







