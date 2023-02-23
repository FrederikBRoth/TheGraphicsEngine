#ifndef ENTITY_H
#define ENTITY_H
#include <controls/AABB.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/detail/type_vec3.hpp>
#include <chunk/ChunkController.h>
class Entity {
private:
	AABB boundingBox;
	glm::vec3 position, scale, rotation;
public:
	MeshBuffer* mb;
	RenderInformation ri;
	glm::vec3* getPosition();
	void checkCollision(ChunkController* cc);
	void makeMesh();
	Entity(glm::vec3 dimension, glm::vec3 position);

};

#endif