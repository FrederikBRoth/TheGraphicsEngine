#include <entities/Item.h>

Item::Item(glm::vec3 collisionBox, glm::vec3 position, BlockType name) : Entity(collisionBox, position, 0.0f, glm::vec3(1.f, 1.f, 1.f))
{
	this->name = name;
}

Item::Item(glm::vec3 collisionBox, glm::vec3 position, BlockType name, float yaw, glm::vec3 scale) : Entity(collisionBox, position, yaw, scale)
{
	this->name = name;
}

void Item::update()
{
	if (grounded) {
		velocity.x *= 0.91f;
		velocity.z *= 0.91f;
	}
	velocity.x *= 0.98f;
	velocity.z *= 0.98f;
}
