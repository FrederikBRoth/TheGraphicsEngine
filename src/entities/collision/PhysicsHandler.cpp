#include <entities\collision\PhysicsHandler.h>

void PhysicsHandler::update(std::vector<Entity*> entities, ChunkController* cc)
{
	for (auto& entity : entities) {
		entity->checkCollision(cc);
		entity->update();
		if (entity->velocity.y > -0.2) {
			entity->velocity.y -= 0.0005f;
		}
		if (abs(entity->velocity.x) < 0.001f && abs(entity->velocity.z) < 0.001f) {
			entity->interactable = true;
		}
		int test = 0;
	}
}
