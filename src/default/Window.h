#ifndef WINDOW_H
#define WINDOW_H
#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <string>
#include <controls/Camera.h>
#include <world/World.h>
#include <chunk/ChunkController.h>
#include <controls/LineTrace.h>
#include <controls/player/Player.h>
#include <entities/Item.h>

class Window
{
private:
	int width, height;
	float deltaTime, lastFrame, lastX, lastY;
	bool traced, detailedTraced, firstMouse, jumped, jetpack, jetpackToggle, spawnItem;
	std::string title;
	World* world;
	ChunkController* cc;
	Player* player;
	static Window* sWindow;
public:
	GLFWwindow* glWindow;
	Window(int width, int height, std::string title, Player* player, World* world, ChunkController* cc);
	void start();
	void processInput(Player* player);
	void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);
	void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	void updateDeltaTime();
	float getDeltaTime();
	static void staticMouseCallback(GLFWwindow* window, double xposIn, double yposIn);
	static void staticScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void setWindow(Window* window);
};
#endif // !WINDOW_H
