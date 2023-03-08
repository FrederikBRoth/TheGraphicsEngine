#ifndef MOB_H
#define MOB_H
#include <entities/Entity.h>


class Mob : public Entity
{
	std::string name;
	Mob(glm::vec3 collisionBox, glm::vec3 position, std::string name, float yaw, glm::vec3 scale);


	// Inherited via Entity
	virtual void update() override;
};
#endif // !NPCENTITY_H
