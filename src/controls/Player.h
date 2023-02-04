#include <controls/AABB.h>
#include <controls/Camera.h>
#include <unordered_map>
#include <world/WorldUtils.h>
#include <chunk/Block.h>
#ifndef PLAYER_H
#define PLAYER_H
class Player
{
private:
	float velocity;
	AABB boundingBox;
	void checkCollision();
public:
	void update(Camera& camera, std::unordered_map<VectorXZ, Block*> chunkMap);
};
#endif
