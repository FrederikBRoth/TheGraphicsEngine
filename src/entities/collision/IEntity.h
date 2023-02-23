#ifndef ENTITY_H
#define ENTITY_H
#include <controls/AABB.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/detail/type_vec3.hpp>
class IEntity {
private:
	AABB* boundingBox;
	glm::vec3 position;
public:
	void checkCollision(ChunkController* cc);
};

#endif