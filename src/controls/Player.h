#include <controls/AABB.h>
#include <controls/Camera.h>
#include <unordered_map>
#include <world/WorldUtils.h>
#include <chunk/Chunk.h>
#ifndef PLAYER_H
#define PLAYER_H
class Player
{
private:
	AABB* boundingBox;
	void checkCollision(Camera& camera, std::unordered_map<VectorXZ, Chunk*>* chunkMap, glm::vec3 velocity);
	bool grounded;
	float acceleration;
public:
	void update(Camera& camera, std::unordered_map<VectorXZ, Chunk*>* chunkMap);
	Player();
	~Player();
};
#endif
