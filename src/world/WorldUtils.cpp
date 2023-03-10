#include <world/WorldUtils.h>

bool operator==(const VectorXZ& left, const VectorXZ& right) noexcept
{
	return (left.x == right.x) && (left.z == right.z);
}

namespace tge {
	glm::ivec3 getBlockPosition(glm::vec3& position)
	{
		return glm::ivec3(floor(position.x * 2), floor(position.y * 2), floor(position.z * 2));
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
	float quadraticInterpolation(glm::vec2 roots, float growth, float x) {
		return growth * (x + roots.x) * (x + roots.y);
	}
	int getIndex(int x, int y, int z)
	{
		return z * CHUNKAREA + y * CHUNKSIZE_X + x;
	}

	int getIndexFromWorldPos(int x, int y, int z)
	{
		int chunkX = tge::modulus(x, 16);
		int chunkZ = tge::modulus(z, 16);
		int chunkY = abs(y);
		return (chunkZ * CHUNKAREA + chunkY * CHUNKSIZE_X + chunkX);
	}

	VectorXZ getKey(int x, int z)
	{
		return { x, z };
	}

	std::string getBlockName(BlockType type)
	{
		switch (type) {
		case BlockType::AIR:
			return "Air";
		case BlockType::DIRT:
			return "Dirt";
		case BlockType::GRASS:
			return "Grass";
		case BlockType::LEAF:
			return "Leaf";
		case BlockType::STONE:
			return "Stone";
		case BlockType::WATER:
			return "Water";
		case BlockType::WOOD:
			return "Wood";
		case BlockType::NOTHING:
			return "Nothing";
		default:
			return "No block with that type is described in the get block name function";
		}
	}

	float difference(float a, float b) {
		float result = abs(a) - abs(b);
		return abs(result);
	}

	std::string getPath(std::string item)
	{
		return std::string(ROOT_DIR + item);
	}

}


