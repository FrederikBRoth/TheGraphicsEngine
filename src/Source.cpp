#pragma once
#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <rendering/Shader.h>
#include <controls/Camera.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <entities/Mesh.h>
#include <entities/IndexedMesh.h>
#include <chunk/Chunk.h>
#include <chunk/ChunkBuilder.h>
#include <texturing/TextureMap.h>
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 750;

// camera
Camera camera(glm::vec3(-0.5f, 1.4f, 3.5f), glm::vec3(0.0f, 1.0f, 0.0f), -63.f, -18.0f);
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

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
}


//void loadTexture(unsigned int texture, const char* filepath, int type = GL_MIRRORED_REPEAT, int colorType = GL_RGB) {
//	glBindTexture(GL_TEXTURE_2D, texture);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, type);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, type);
//	//Sets the texture filtering based on if the texture is upscaled on a larger object or downscaled if on a smaller object
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	int width, height, nrChannels;
//	unsigned char* data = stbi_load(filepath, &width, &height,
//		&nrChannels, 0);
//	if (data) {
//		glTexImage2D(GL_TEXTURE_2D, 0, colorType, width, height, 0, colorType,
//			GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else {
//		std::cout << "Failed to load texture" << std::endl;
//	}
//	stbi_image_free(data);
//}

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
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
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
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
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
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f
	};
	std::vector<unsigned int> indices{
		0, 1, 3,
		1, 2, 3
	};
	Mesh* e = new Mesh(vertices, 36);
	Mesh* e2 = new Mesh(vertices2, 36);
	Mesh* e3 = new Mesh(triangleTestvert2, 6);
	IndexedMesh* i = new IndexedMesh(indices, triangleTestvert);
	Chunk* chunk = new Chunk(glm::vec3(1.0f));
	chunk->createSolidChunk();
	TextureMap* tm = new TextureMap(std::string("assets/textures/TextureTable.png"), 16, 16);
	ChunkBuilder* builder = new ChunkBuilder(chunk, tm->getTexCoords(2, 0));
	RenderInformation ri = builder->getChunkMesh();
	IndexedMesh* chunkMesh = new IndexedMesh(ri);
	//texture load

	//unsigned int EBO;
	//glGenBuffers(1, &EBO);


	tm->loadTexture(GL_RGBA);

	//Can also be GL_STREAM_DRAW: Only used very little, GL_DYMANIC DRAW: Used a lot, but the data is changed aswell a lot
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection;

	Shader lighting = Shader("LightingShader.vert", "LightingShader.frag");
	Shader lightSource = Shader("LightSourceShader.vert", "LightSourceShader.frag");

	glEnable(GL_DEPTH_TEST);

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	const float radius = 1.0f;
	while (!glfwWindowShouldClose(window))
	{
		//Gets the current frame for input processing
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);

		float camX = sin((float)glfwGetTime()) * radius;
		float camZ = cos((float)glfwGetTime()) * radius;

		lightPos = glm::vec3(camX, 0.0f, camZ);

		//Clears the screen for the new frame render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Binds the normal cube
		//Sets projection matrices
		view = camera.GetViewMatrix();
		projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		model = glm::mat4(1.0f);
		//Enables normal cube Shader and sets uniform variables
		lighting.use();
		lighting.setMat4("model", model);
		lighting.setMat4("view", view);
		lighting.setMat4("projection", projection);
 		lighting.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		lighting.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		lighting.setVec3("lightPos", lightPos);
		lighting.setVec3("viewPos", camera.Position);
		tm->bind();
		chunkMesh->render();

		e->render();

		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.0f));
		//lighting.setMat4("model", model);



		////Preps light source cube 
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, lightPos);
		//model = glm::scale(model, glm::vec3(0.2f));
		//lightSource.use();
		//lightSource.setMat4("model", model);
		//lightSource.setMat4("view", view);
		//lightSource.setMat4("projection", projection);
		//e->render();



		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	std::cout << camera.Position.x << ", " << camera.Position.y << ", " << camera.Position.z << " | " << camera.Yaw << ", " << camera.Pitch << std::endl;

	glfwTerminate();
	return 0;
}

