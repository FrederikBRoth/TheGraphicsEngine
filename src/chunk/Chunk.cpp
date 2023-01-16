#include <chunk/Chunk.h>

const siv::PerlinNoise Chunk::perlin = siv::PerlinNoise(seed);

Chunk::Chunk(glm::vec3 position)
{
	this->position = position;
	this->chunk = std::vector<Block*>(CHUNKVOLUME);
	this->noiseMap = std::vector<int>();
	generateNoiseMap(noiseMap, position);
}

void Chunk::generateNoiseMap(std::vector<int>& noiseMap, glm::vec3& position)
{

	int magnitude = 2;
	for (int x = position.x; x < position.x + CHUNKSIZE_X; x++) {
		for (int z = position.z; z < position.z + CHUNKSIZE_Z; z++) {


			double n = perlin.octave2D_01((x),(z), 10, 1.0);
			noiseMap.push_back(floor(magnitude*n));
		}
	}
}

Chunk::~Chunk()
{
	for (auto block : chunk) {
		delete block;
	}
	this->chunk.clear();
	this->chunk.shrink_to_fit();
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

void Chunk::createPseudoRealChunk()
{
	int height = CHUNKSIZE_Y / 2;
	int grass = CHUNKSIZE_Y / 2 - 1;
	for (int i = 0; i < CHUNKVOLUME; i++) {
		int x = i % CHUNKSIZE_X;
		int y = (i / CHUNKSIZE_Z) % CHUNKSIZE_Y;
		int z = i / (CHUNKSIZE_X * CHUNKSIZE_Y);
		int offset = noiseMap[z * CHUNKSIZE_X + x];

		if (y < height + offset) {
			if (y == grass + offset) {
				chunk[i] = new Block(BlockType::GRASS);
			}
			else if(y < grass + offset && y > grass + offset - 3){
				chunk[i] = new Block(BlockType::DIRT);
			}
			else {
				chunk[i] = new Block(BlockType::STONE);

			}
		}
		else {
			chunk[i] = new Block(BlockType::AIR);
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









