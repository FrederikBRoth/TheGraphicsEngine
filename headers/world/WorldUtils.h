#ifndef WORLDUTILS_H
#define WORLDUTILS_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/detail/type_vec3.hpp>
#include <math.h>
#include <world/Constants.h>
namespace tge {
	glm::ivec3 getBlockPosition(glm::vec3& position);
	glm::ivec3 getChunkPosition(glm::ivec3& worldPos);
	int modulus(int a, int b);
	float logisticInterpolation(float limit, float growth, float x);
	int getIndex(int x, int y, int z);
	
}

#endif // !WORLDUTILS_H
