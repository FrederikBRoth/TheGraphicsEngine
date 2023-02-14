#include <controls/AABB.h>
#include <controls/Camera.h>
#include <unordered_map>
#include <world/WorldUtils.h>
#include <chunk/Chunk.h>
#include <map>
#ifndef PLAYER_H
#define PLAYER_H
class Player
{
private:
	AABB* boundingBox;
	void checkCollision(Camera& camera, std::unordered_map<VectorXZ, Chunk*>* chunkMap, glm::vec3 velocity);
	bool grounded;
	float acceleration;
	glm::ivec3 velocity;
	glm::ivec3 accelerations;
	//Should probably be its own and also something better and more generic. This will suffice for now
	std::map<BlockType, int> inventory;
public:
	void update(Camera& camera, std::unordered_map<VectorXZ, Chunk*>* chunkMap);
	bool gravity;
	void addItem(BlockType type);
	Player();
	~Player();
};
#endif
