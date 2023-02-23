#ifndef PHYSICS_H
#define PHYSICS_H
#include <vector>
#include <entities/Entity.h>
class PhysicsHandler
{
private:
	float gravity;

public:
	void update(std::vector<Entity> entities);

};
#endif