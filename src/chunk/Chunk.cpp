#include <chunk/Chunk.h>

Chunk::Chunk(glm::vec3 position)
{
	this->position = position;
	this->chunk = std::vector<std::vector<std::vector<Block*>>>(CHUNKSIZE_X, 
			std::vector<std::vector<Block*>>(CHUNKSIZE_Y, 
				std::vector<Block*>(CHUNKSIZE_Z)));
}

Chunk::~Chunk()
{
	for (auto z : this->chunk) {
		for (auto y : z) {
			for (auto x : y) {
				delete x;
			}
		}
	}
	this->chunk.clear();
	this->chunk.shrink_to_fit();
}

void Chunk::createSolidChunk()
{
	for (int x = 0; x < CHUNKSIZE_X; x++) {
		for (int y = 0; y < CHUNKSIZE_Y; y++) {
			for (int z = 0; z < CHUNKSIZE_Z; z++) {
				this->chunk[x][y][z] = new Block(BlockType::GRASS);	
			}
		}
	}
}

void Chunk::createStripePatternChunk()
{
	for (int x = 0; x < CHUNKSIZE_X; x++) {
		for (int y = 0; y < CHUNKSIZE_Y; y++) {
			for (int z = 0; z < CHUNKSIZE_Z; z++) {
				if (y % 2 == 0) {
					this->chunk[x][y][z] = new Block(BlockType::GRASS);
				}
				else {
					this->chunk[x][y][z] = new Block(BlockType::AIR);
				}
			}
		}
	}
}

void Chunk::createStairsChunk()
{
	for (int x = 0; x < CHUNKSIZE_X; x++) {
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
	}
}







//Blockfaces can be stores as constant arrays of 12 values
//These values indicate the triangle position ie "0, 0, 1" is
//a triange that moves in depth 1 on one of its points