
#ifndef WORLD_H
#define WORLD_H
#include <chunk/Chunk.h>

#include <vector>
#include <glm/detail/type_vec3.hpp>
#include <math.h>
#include <string>
#include <texturing/TextureMap.h>
#include <world/WorldUtils.h>
class Entity;
class World
{
public:
	std::vector<Entity*> entities;
	glm::ivec3 worldPos;
	void updateWorldPosition(glm::vec3& position);
	glm::vec3 getWorldPosition();
	glm::vec3 getChunkWorldPosition();
	void update();
	World();
};
#endif // !WORLD_H
