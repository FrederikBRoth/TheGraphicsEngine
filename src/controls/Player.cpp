#include <controls/Player.h>

void Player::checkCollision(Camera& camera, std::unordered_map<VectorXZ, Chunk*>* chunkMap)
{
	glm::vec3 minDim = tge::getBlockPosition(camera.Position - boundingBox->dimension);
	glm::vec3 maxDim = tge::getBlockPosition(camera.Position + boundingBox->dimension);

	for (int x = minDim.x; x < maxDim.x; x++) {
		for (int y = minDim.y; y < maxDim.y; y++) {
			for (int z = minDim.z; z < maxDim.z; z++) {
				glm::ivec3 chunkPosition = tge::getChunkPosition(glm::ivec3( x, y, z ));
				VectorXZ key = tge::getKey(chunkPosition.x, chunkPosition.z);
				int index = tge::getIndexFromWorldPos(x, y, z);
				if (chunkMap->count(key)) {
					if (index < 0 || index >= CHUNKVOLUME) {
						return;
					}
					Block* block = chunkMap->at(key)->chunk[index];
					
					
				}
				
			}
		}
	}
	std::cout << "__________________________________________" << std::endl;

}

void Player::update(Camera& camera, std::unordered_map<VectorXZ, Chunk*>* chunkMap)
{
	boundingBox->updateBB(camera.Position);
	checkCollision(camera, chunkMap);
}

Player::Player()
{
	boundingBox = new AABB({ 0.3f, 1.f, 0.3f });
}

Player::~Player()
{
	delete boundingBox;
}
