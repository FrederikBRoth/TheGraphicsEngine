#ifndef PLAYER_H
#define PLAYER_H
#include <controls/AABB.h>
#include <controls/Camera.h>
#include <unordered_map>
#include <world/WorldUtils.h>
#include <chunk/Chunk.h>
#include <map>
#include <controls/player/Inventory.h>
#include <world/World.h>
#include <entities/Item.h>

class Player
{
private:
	AABB* boundingBox;
	void checkCollision(Camera& camera, std::unordered_map<VectorXZ, Chunk*>* chunkMap, glm::vec3 velocity);
	bool grounded, canJump;
	float acceleration;
	glm::ivec3 velocity;
	glm::ivec3 accelerations;
	glm::vec3 position;
	float yaw;
	//Should probably be its own and also something better and more generic. This will suffice for now
public:
	Camera* camera;
	Inventory* inventory;
	void update(Camera& camera, std::unordered_map<VectorXZ, Chunk*>* chunkMap, World* world);
	bool gravity;
	void dropItem(World* world, MeshBuilder* mb);
	void pickupItems(World* world);
	void jump();
	Player(Camera* camera);
	~Player();
};
#endif
