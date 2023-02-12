#ifndef WORLDUTILS_H
#define WORLDUTILS_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/detail/type_vec3.hpp>
#include <math.h>
#include <world/Constants.h>
#include <string>
#include <functional>
#include <chunk/Block.h>
struct VectorXZ {
	int x, z;
};

bool operator==(const VectorXZ& left, const VectorXZ& right) noexcept;

namespace std {
	template <> struct hash<VectorXZ> {
		size_t operator()(const VectorXZ& vect) const noexcept
		{
			std::hash<decltype(vect.x)> hasher;

			auto hash1 = hasher(vect.x);
			auto hash2 = hasher(vect.z);

			return std::hash<decltype(vect.x)>{}((hash1 ^ hash2) >> 2);
		}
	};
}

namespace tge {

	glm::ivec3 getBlockPosition(glm::vec3& position);
	glm::ivec3 getChunkPosition(glm::ivec3& worldPos);
	int modulus(int a, int b);
	float logisticInterpolation(float limit, float growth, float x);
	int getIndex(int x, int y, int z);
	int getIndexFromWorldPos(int x, int y, int z);
	VectorXZ getKey(int x, int z);
	std::string getBlockName(BlockType type);
}


#endif // !WORLDUTILS_H
