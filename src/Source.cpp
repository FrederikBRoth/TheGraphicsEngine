#pragma once
#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <rendering/Shader.h>
#include <controls/Camera.h>
#include <stb_image.h>
#include <entities/Mesh.h>
#include <entities/IndexedMesh.h>
#include <chunk/Chunk.h>
#include <chunk/ChunkBuilder.h>
#include <texturing/TextureMap.h>
#include <chrono>
#include <world/World.h>
#include <chunk/ChunkGenerator.h>
#include <chunk/ChunkController.h>
#include <controls/LineTrace.h>
#include <entities/Line.h>
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 750;

// camera
Camera camera(glm::vec3(-0.5f, 1.4f, 3.5f), glm::vec3(0.0f, 1.0f, 0.0f), -63.f, -18.0f);
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
World* world = new World();
ChunkController* cc = new ChunkController(world);
//traces
bool traced = false;
// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		cc->updateChunk(world->getChunkWorldPosition().x, 0, world->getChunkWorldPosition().z);
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && !traced) {
		/*for (int i = 1; i < (int)DISTANCE / STEPSIZE; i++) {
			glm::vec3 step = (camera.Position + (camera.Front * ((float)i * STEPSIZE)));
			std::vector<float> linevert{ camera.Position.x , camera.Position.y , camera.Position.z, step.x, step.y, step.z };

			lines.insert(lines.end(), new Line(linevert, 2));
		}*/
		glm::vec3 trace = LineTrace::trace(camera.Position, camera.Front, cc);
		traced = true;

		//std::cout << trace.x << ", " << trace.y << ", " << trace.z << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_RELEASE && traced) {
		traced = false;
	}
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}


int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Window setup
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//Triangle setup
	std::vector<float> vertices {
		// positions // normals // texture coords
		
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		
		0.5f, 0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f

	};
	std::vector<float> vertices2 {
		// positions // normals // texture coords
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		1.5f, 0.5f, 0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		1.5f, 1.5f, 0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		1.5f, 1.5f, 0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		0.5f, 1.5f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 1.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		1.5f, 0.5f, 1.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		1.5f, 1.5f, 1.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		1.5f, 1.5f, 1.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 1.5f, 1.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 1.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, 1.5f, 1.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 1.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 1.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 1.5f, 1.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		1.5f, 1.5f, 1.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		1.5f, 1.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		1.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		1.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		1.5f, 0.5f, 1.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.5f, 1.5f, 1.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		1.5f, 0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		1.5f, 0.5f, 1.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		1.5f, 0.5f, 1.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 1.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 1.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		1.5f, 1.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		1.5f, 1.5f, 1.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		1.5f, 1.5f, 1.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 1.5f, 1.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 1.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};

	std::vector<float> triangleTestvert{
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f
	};
	std::vector<float> triangleTestvert2{
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f
	};
	std::vector<float> lineTest{
		5.5f, 5.5f, 5.5f, 0.5f, 0.5f, -0.5f
	};
	std::vector<unsigned short> indices{
		0, 1, 3,
		1, 2, 3
	};
	Mesh e = Mesh(vertices, 36);
	Mesh* e2 = new Mesh(vertices2, 36);
	Mesh* e3 = new Mesh(triangleTestvert2, 6);
	TextureMap* tm = new TextureMap(std::string("assets/textures/TextureTable.png"), 16, 16);
	

	
	tm->loadTexture(GL_RGBA);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection;

	Shader lighting = Shader("LightingShader.vert", "LightingShader.frag");
	Shader lightSource = Shader("LightSourceShader.vert", "LightSourceShader.frag");
	Shader lineS = Shader("LineShader.vert", "LineShader.frag");


	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	tm->bind();

	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	const float radius = 1.0f;
	while (!glfwWindowShouldClose(window))
	{
		world->updateWorldPosition(camera.Position);
		//Gets the current frame for input processing
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);
		glm::vec3 chunkPos = world->getChunkWorldPosition();

		//std::cout << "X: " << world->worldX << " Y: " << world->worldY << "d Z: " << world->worldZ << " | ";
		//std::cout << "X: " << chunkPos.x << " Y: " << chunkPos.y << " Z: " << chunkPos.z << std::endl;

		float camX = sin((float)glfwGetTime()) * radius;
		float camZ = cos((float)glfwGetTime()) * radius;

		lightPos = glm::vec3(camX, 0.0f, camZ);
		lightPos = glm::vec3(5.0f, 10.0f, 5.0f);
		//Clears the screen for the new frame render
		glClearColor(0.44f, 0.73f, 0.83f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Binds the normal cube
		//Sets projection matrices
		view = camera.GetViewMatrix();
		projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		model = glm::mat4(1.0f);

		model = glm::mat4(1.0f);
		lighting.use();
		lighting.setMat4("model", model);
		lighting.setMat4("view", view);
		lighting.setMat4("projection", projection);
 		lighting.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		lighting.setVec3("lightColor", 0.95f, 0.9f, 0.65f);
		lighting.setVec3("lightPos", lightPos);
		lighting.setVec3("viewPos", camera.Position);
		cc->update();

		model = glm::translate(model, glm::vec3(10.0f, 0.0f, 0.0f));
		lighting.setMat4("model", model);

		e3->render();
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.0f));
		//lighting.setMat4("model", model);
		



		//Preps light source cube 
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lightSource.use();
		lightSource.setMat4("model", model);
		lightSource.setMat4("view", view);
		lightSource.setMat4("projection", projection);
		e.render();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(5.0f, 10.0f, 5.0f));
		lightSource.setMat4("model", model);
		e.render();



		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	std::cout << camera.Position.x << ", " << camera.Position.y << ", " << camera.Position.z << " | " << camera.Yaw << ", " << camera.Pitch << std::endl;

	glfwTerminate();
	return 0;
}

