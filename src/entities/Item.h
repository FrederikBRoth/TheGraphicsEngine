#ifndef ITEM_H
#define ITEM_H
#include <entities/Entity.h>
class Item : public Entity
{
private:
public:
	std::string name;
	Item(glm::vec3 collisionBox, glm::vec3 position, std::string name);

	Item(glm::vec3 collisionBox, glm::vec3 position, std::string name, float yaw, glm::vec3 scale);

};
#endif
