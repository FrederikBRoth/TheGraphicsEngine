#include <entities/Item.h>

Item::Item(glm::vec3 collisionBox, glm::vec3 position, std::string name) : Entity(collisionBox, position, 0.0f, 1.0f)
{
	this->name = name;
}

Item::Item(glm::vec3 collisionBox, glm::vec3 position, std::string name, float yaw, float scale) : Entity(collisionBox, position, yaw, scale)
{
	this->name = name;
}
