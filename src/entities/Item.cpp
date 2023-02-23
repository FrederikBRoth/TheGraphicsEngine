#include <entities/Item.h>

Item::Item(glm::vec3 collisionBox, glm::vec3 position, std::string name) : Entity(collisionBox, position)
{
	this->name = name;
}


