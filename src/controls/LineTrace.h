#ifndef LINETRACE_H
#define LINETRACE_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chunk/ChunkController.h>
#include <world/WorldUtils.h>
#include <controls/player/Player.h>
constexpr float DISTANCE = 5.0f;
constexpr float STEPSIZE = 0.001f;

class LineTrace
{
public:
	static BlockType remove(glm::vec3& playerPos, glm::vec3& playerFront, ChunkController* cc);
	static glm::vec3 create(glm::vec3& playerPos, glm::vec3& playerFront, ChunkController* cc, Player* player);


};
#endif LINETRACE_H
