#include <entities/Entity.h>



float Entity::getRotation()
{
	return yaw;
}

void Entity::checkCollision(ChunkController* cc, glm::vec3 velocity)
{
	glm::vec3 minDim = tge::getBlockPosition(position - boundingBox.dimension);

	glm::vec3 maxDim = tge::getBlockPosition(position + boundingBox.dimension);
	for (int x = minDim.x; x <= maxDim.x; x++) {
		for (int y = minDim.y; y <= maxDim.y; y++) {
			for (int z = minDim.z; z <= maxDim.z; z++) {
				glm::ivec3 chunkPosition = tge::getChunkPosition(glm::ivec3(x, y, z));
				VectorXZ key = tge::getKey(chunkPosition.x, chunkPosition.z);
				int index = tge::getIndexFromWorldPos(x, y, z);
				if (cc->chunkMap.count(key)) {
					if (index < 0 || index >= CHUNKVOLUME) {
						return;
					}
					Block* block = cc->chunkMap.at(key)->chunk[index];
					if (block != nullptr && block->isCollidable) {
						//The minus 0.001f is to eliminate floating point errors due to my stupid way of implementing collision
						if (velocity.y > 0) {
							position.y = float(y) / 2.0f - boundingBox.dimension.y / 0.001f;
						}
						else if (velocity.y < 0) {
							position.y = float(y) / 2.0f + boundingBox.dimension.y + 0.5f;
							grounded = true;

						}
						if (velocity.x > 0) {
							position.x = float(x) / 2.0f - boundingBox.dimension.x - 0.001f;
						}
						else if (velocity.x < 0) {
							position.x = float(x) / 2.0f + boundingBox.dimension.x + 0.5f;
						}
						if (velocity.z > 0) {
							position.z = float(z) / 2.0f - boundingBox.dimension.z - 0.001f;
						}
						else if (velocity.z < 0) {
							position.z = float(z) / 2.0f + boundingBox.dimension.z + 0.5f;
						}
					}
				}
			}
		}
	}
}

void Entity::checkCollision(ChunkController* cc)
{
	grounded = false;
	position.x += velocity.x;
	checkCollision(cc, { velocity.x, 0.0f, 0.0f });
	position.y += velocity.y;
	checkCollision(cc, { 0.0f, velocity.y, 0.0f });
	position.z += velocity.z;
	checkCollision(cc, { 0.0f, 0.0f, velocity.z });
}

void Entity::makeMesh()
{
	mb->loadMesh(ri, MeshConfig(8, true, true, MeshShape::TRIANGLE));
	mb->bind();
}

Entity::Entity(glm::vec3 dimension, glm::vec3 position, float yaw, glm::vec3 scale)
{
	interactable = false;
	boundingBox = AABB(dimension);
	this->position = position;
	this->scale = scale;
	this->yaw = yaw;
	velocity = glm::vec3(0.05f, 0.05f, 0.05f);
	calcVelocity = glm::vec3(0.05f, 0.05f, 0.05f);

	mb = new MeshBuffer();
}

Entity::~Entity()
{
}
