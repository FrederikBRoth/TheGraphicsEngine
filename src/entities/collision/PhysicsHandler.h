#ifndef PHYSICS_H
#define PHYSICS_H
#include <vector>
#include <entities/Entity.h>
class PhysicsHandler
{
private:
	float gravity = 0.2f;
	float step = 0.0005f;
public:
	void update(std::vector<Entity*> entities, ChunkController* cc);

};
#endif