#include <world/WorldUtils.h>
bool operator==(const VectorXZ& left, const VectorXZ& right) noexcept
{
	return (left.x == right.x) && (left.z == right.z);
}

namespace tge {
	glm::ivec3 getBlockPosition(glm::vec3& position)
	{
		return glm::ivec3((position.x * 2), (position.y * 2), (position.z * 2));
	}
	glm::ivec3 getChunkPosition(glm::ivec3& worldPos)
	{
		glm::ivec3 chunkPos(worldPos.x / CHUNKSIZE_X, worldPos.y, worldPos.z / CHUNKSIZE_Z);
		if (worldPos.x < 0) {
			chunkPos.x = (worldPos.x + 1) / 16 - 1;
		}
		if (worldPos.y < 0) {
			chunkPos.y += -1;
		}
		if (worldPos.z < 0) {
			chunkPos.z = (worldPos.z + 1) / 16 - 1;
		}
		return chunkPos;
	}
	int modulus(int a, int b)
	{
		return (a % b + b) % b;
	}

	float logisticInterpolation(float limit, float growth, float x)
	{
		
		return limit / (1 + expf(growth * x)) - limit/2.0f;
		
	}

	int getIndex(int x, int y, int z)
	{
		return z * CHUNKAREA + y * CHUNKSIZE_X + x;
	}

	VectorXZ getKey(int x, int z)
	{
		return { x, z };
	}

}


