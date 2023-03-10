#include <entities\collision\PhysicsHandler.h>

void PhysicsHandler::update(std::vector<Entity*> entities, ChunkController* cc, Window* window)
{
	for (auto& entity : entities) {

		entity->checkCollision(cc);
		entity->update();
		if (entity->velocity.y > -gravity) {
			entity->velocity.y -= step;
		}
	}
}
