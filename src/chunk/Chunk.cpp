#include <includes/chunk/Chunk.h>
namespace {

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
	0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1 };


Chunk::Chunk(glm::vec3 location)
{
	this->location = location;
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
	for (int z = 0; z < CHUNKSIZE_Z; z++) {
		for (int y = 0; y < CHUNKSIZE_Y; y++) {
			for (int x = 0; x < CHUNKSIZE_X; x++) {
				this->chunk[z][y][x] = new Block(BlockType::GRASS);
			}
		}
	}
}

RenderInformation Chunk::getMesh()
{
	RenderInformation ri = RenderInformation();
	/*for (int z = 0; z < CHUNKSIZE_Z; z++) {
		for (int y = 0; y < CHUNKSIZE_Y; y++) {
			for (int x = 0; x < CHUNKSIZE_X; x++) {
				if (this->chunk[z][y][x]->type != BlockType::AIR) {
					ri.vertices.push_back()
				}
			}
		}
	}*/
	return ri;
}
}



//Blockfaces can be stores as constant arrays of 12 values
//These values indicate the triangle position ie "0, 0, 1" is
//a triange that moves in depth 1 on one of its points