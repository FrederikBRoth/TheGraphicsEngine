#ifndef LINETRACE_H
#define LINETRACE_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <entities/Line.h>
constexpr float DISTANCE = 20.0f;
class LineTrace
{
public:
	static glm::vec3 trace(glm::vec3 playerPos, glm::vec3 playerFront);
};
#endif LINETRACE_H
