#include <chunk/Chunk.h>


Chunk::Chunk(glm::vec3 position)
{
	this->position = position;
	this->chunk = std::vector<Block*>(CHUNKVOLUME);
	solidMesh = new MeshBuffer();
	waterMesh = new MeshBuffer();

}


Chunk::~Chunk()
{
	for (auto block : chunk) {
		delete block;
	}
	this->chunk.clear();
	this->chunk.shrink_to_fit();
	delete this->solidMesh;
	delete this->waterMesh;
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

void Chunk::createPerlinNoiseChunk(std::vector<int>& noiseMap, TreeGeneration* tg)
{
	std::vector<glm::ivec3> trees;
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
				//Incredibly stupid way to spawn a tree, but just for testing REMOVE A ONCE
				if (offset < -8 && x > 4 && x < 12 && z > 4 && z < 12) {
					trees.push_back(glm::ivec3(x, y, z));
				}
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
	if (trees.size() > 0) {
		int randomIndex = rand() % trees.size();
		tg->placeTree(trees[randomIndex], chunk);
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

void Chunk::changeBlock(glm::ivec3 pos, BlockType block)
{
	int index = tge::getIndex(pos.x, pos.y, pos.z);
	if (index < 0) {
		int brekk = 0;
	}
	chunk[index]->type = block;

}

Block* Chunk::getLocalBlock(int x, int y, int z)
{
	return nullptr;
}









