#include <controls/player/Player.h>

void Player::checkCollision(Camera& camera, std::unordered_map<VectorXZ, Chunk*>* chunkMap, glm::vec3 velocity)
{
	glm::vec3 minDim = tge::getBlockPosition(camera.Position - boundingBox->dimension);
	glm::vec3 maxDim = tge::getBlockPosition(camera.Position + boundingBox->dimension);
	for (int x = minDim.x; x <= maxDim.x; x++) {
		for (int y = minDim.y; y <= maxDim.y-1; y++) {
			for (int z = minDim.z; z <= maxDim.z; z++) {
				glm::ivec3 chunkPosition = tge::getChunkPosition(glm::ivec3( x, y, z ));
				VectorXZ key = tge::getKey(chunkPosition.x, chunkPosition.z);
				int index = tge::getIndexFromWorldPos(x, y, z);
				if (chunkMap->count(key)) {
					if (index < 0 || index >= CHUNKVOLUME) {
						return;
					}
					Block* block = chunkMap->at(key)->chunk[index];
					if(block != nullptr && block->isCollidable) {
						//The minus 0.001f is to eliminate floating point errors due to my stupid way of implementing collision
						if (velocity.y > 0) {
							camera.Position.y = float(y) / 2.0f - boundingBox->dimension.y / 2.0f + 0.1f;
						}
						else if (velocity.y < 0) {
							camera.Position.y = float(y) / 2.0f + boundingBox->dimension.y + 0.5f;
							grounded = true;
						}
						if (velocity.x > 0) {
							camera.Position.x = float(x) / 2.0f - boundingBox->dimension.x - 0.001f;
						}
						else if (velocity.x < 0) {
							camera.Position.x = float(x) / 2.0f + boundingBox->dimension.x + 0.5f;
						}
						if (velocity.z > 0) {
							camera.Position.z = float(z) / 2.0f - boundingBox->dimension.z - 0.001f;
						}
						else if (velocity.z < 0) {
							camera.Position.z = float(z) / 2.0f + boundingBox->dimension.z + 0.5f;
						}
					}		
				}	
			}
		}
	}
}

void Player::update(Camera& camera, std::unordered_map<VectorXZ, Chunk*>* chunkMap, World* world)
{
	grounded = false;
	camera.Position.x += camera.relativeVelocity.x;
	checkCollision(camera, chunkMap, {camera.relativeVelocity.x, 0.0f, 0.0f});
	camera.Position.y += camera.relativeVelocity.y;
	checkCollision(camera, chunkMap, {0.0f, camera.relativeVelocity.y,  0.0f });
	camera.Position.z += camera.relativeVelocity.z;
	checkCollision(camera, chunkMap, { 0.0f, 0.0f, camera.relativeVelocity.z });
	if (!grounded && gravity) {
		if (camera.relativeVelocity.y > -0.25f) {
			camera.relativeVelocity.y -= 0.0015f;
		}
	}
	else {
		camera.relativeVelocity.y = 0.0f;
	}
	boundingBox->updateBB(camera.Position);
	yaw = camera.Yaw;
	position = camera.Position;
	pickupItems(world);
	
}

void Player::dropItem(World* world, MeshBuilder* mb)
{
	BlockType type = inventory->removeItem();
	if (type != BlockType::NOTHING) {
		Item* item = new Item(glm::vec3(0.3f, 0.3f, 0.3f), position, type, yaw, glm::vec3(0.1f, 0.1f, 0.1f));
		item->velocity *= camera->Front;


		mb->addSingleBlock(&item->ri, mb->ti->blockInfo[type], &glm::vec3(0.0f, 0.0f, 0.0f));
		item->makeMesh();
		world->entities.insert(world->entities.begin(), item);	
	}
}

void Player::pickupItems(World* world) {
	glm::vec3 minDim = position - boundingBox->dimension;
	glm::vec3 maxDim = position + boundingBox->dimension;
	std::vector<Entity*>::iterator it = world->entities.begin();
	while (it != world->entities.end()) {
		
		if ((*it)->interactable &&
			minDim.x <= (*it)->position.x &&
			(*it)->position.x <= maxDim.x &&
			minDim.y <= (*it)->position.y &&
			(*it)->position.y <= maxDim.y &&
			minDim.z <= (*it)->position.z &&
			(*it)->position.z <= maxDim.z)
		{
			if (Item* c = dynamic_cast<Item*>(*it)) {
				inventory->addItem(c->name);
			}
			delete (*it);
			it = world->entities.erase(it);
		} 
		else ++it;

	}

}

Player::Player(Camera* camera)
{
	this->camera = camera;
	boundingBox = new AABB({ 0.2f, 0.7f, 0.2f });
	grounded = true;
	acceleration = 0.2f;
	gravity = false;
	inventory = new Inventory();
}

Player::~Player()
{
	delete boundingBox;
	delete inventory;
}
