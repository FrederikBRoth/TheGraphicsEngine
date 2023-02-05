#include <controls/Player.h>

void Player::checkCollision(Camera& camera, std::unordered_map<VectorXZ, Chunk*>* chunkMap, glm::vec3 velocity)
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
					if(block != nullptr) {
						if (block->isCollidable) {
							if (velocity.y > 0) {
								camera.Position.y = float(y) / 2.0f - boundingBox->dimension.y + 0.5111f;
							}
							else if (velocity.y < 0) {
								camera.Position.y = float(y) / 2.0f + boundingBox->dimension.y + 0.5f;

							}

							if (velocity.x > 0) {
								camera.Position.x = float(x) / 2.0f - boundingBox->dimension.x - 0.5f;
							}
							else if (velocity.x < 0) {
								camera.Position.x = float(x) / 2.0f + boundingBox->dimension.x;
							}

							if (velocity.z > 0) {
								camera.Position.z = float(z) / 2.0f - boundingBox->dimension.z;
							}
							else if (velocity.z < 0) {
								camera.Position.z = float(z) / 2.0f + boundingBox->dimension.z + 0.0001f;
							}
						}
					}
					
				}
				
			}
		}
	}


}

void Player::update(Camera& camera, std::unordered_map<VectorXZ, Chunk*>* chunkMap)
{

	camera.Position.x += camera.relativeVelocity.x;
	checkCollision(camera, chunkMap, {camera.relativeVelocity.x, 0.0f, 0.0f});
	camera.Position.y += camera.relativeVelocity.y;
	checkCollision(camera, chunkMap, {0.0f, camera.relativeVelocity.y,  0.0f });
	camera.Position.z += camera.relativeVelocity.z;
	checkCollision(camera, chunkMap, { 0.0f, 0.0f, camera.relativeVelocity.z });
	boundingBox->updateBB(camera.Position);

}

Player::Player()
{
	boundingBox = new AABB({ 1.f, 1.f, 1.f });
}

Player::~Player()
{
	delete boundingBox;
}
