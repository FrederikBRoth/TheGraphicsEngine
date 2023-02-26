#include <entities\collision\PhysicsHandler.h>

void PhysicsHandler::update(std::vector<Entity*> entities, ChunkController* cc)
{
	for (auto& entity : entities) {
		entity->checkCollision(cc);
		entity->velocity.x *= 0.98f;
		entity->velocity.z *= 0.98f;

		int test = 0;
	}
}
