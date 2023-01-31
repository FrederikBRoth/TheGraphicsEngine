#ifndef WINDOW_H
#define WINDOW_H
#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <string>
#include <controls/Camera.h>
#include <world/World.h>
#include <chunk/ChunkController.h>
#include <controls/LineTrace.h>
class Window
{
private:
	int width, height;
	float deltaTime, lastFrame, lastX, lastY;
	bool traced, firstMouse;
	std::string title;
	Camera* camera;
	World* world;
	ChunkController* cc;
	static Window* sWindow;
public:
	GLFWwindow* glWindow;
	Window(int width, int height, std::string title, Camera* camera, World* world, ChunkController* cc);
	void start();
	void addWorld(World* world);
	void addChunkController(ChunkController* cc);
	void processInput();
	void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);
	void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	void updateDeltaTime();

	static void staticMouseCallback(GLFWwindow* window, double xposIn, double yposIn);
	static void staticScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void setWindow(Window* window);
};
#endif // !WINDOW_H
