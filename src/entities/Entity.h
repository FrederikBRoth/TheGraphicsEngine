#pragma once
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
	float yaw;
public:
	MeshBuffer* mb;
	RenderInformation ri;
	glm::vec3 position, scale, velocity, calcVelocity;
	bool interactable, grounded;
	float getRotation();

	void checkCollision(ChunkController* cc, glm::vec3 velocity);
	void checkCollision(ChunkController* cc);
	virtual void update() = 0;
	void makeMesh();
	Entity(glm::vec3 dimension, glm::vec3 position, float yaw, glm::vec3 scale);
	virtual ~Entity();

};

#endif