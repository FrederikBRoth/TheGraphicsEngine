#include <entities/Mob.h>

Mob::Mob(glm::vec3 collisionBox, glm::vec3 position, std::string name, float yaw, glm::vec3 scale) : Entity(collisionBox, position, yaw, scale)
{
	this->name = name;
	velocity = glm::vec3(0.f, 0.f, 0.f);
	calcVelocity = glm::vec3(0.f, 0.f, 0.f);
}

void Mob::update()
{
}
