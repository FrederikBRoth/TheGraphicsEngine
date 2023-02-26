#ifndef ITEM_H
#define ITEM_H
#include <entities/Entity.h>
class Item : public Entity
{
private:
public:
	BlockType name;
	Item(glm::vec3 collisionBox, glm::vec3 position, BlockType name);

	Item(glm::vec3 collisionBox, glm::vec3 position, BlockType name, float yaw, glm::vec3 scale);

};
#endif
