#ifndef LINETRACE_H
#define LINETRACE_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <entities/Line.h>
#include <chunk/ChunkController.h>
constexpr float DISTANCE = 5.0f;
constexpr float STEPSIZE = 0.01f;

class LineTrace
{
public:
	static glm::vec3 trace(glm::vec3& playerPos, glm::vec3& playerFront, ChunkController* cc);

};
#endif LINETRACE_H
