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
#include <default/Window.h>
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 750;

// camera
Camera camera(glm::vec3(-0.5f, 15.0f, 3.5f), glm::vec3(0.0f, 1.0f, 0.0f), -63.f, -18.0f);
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
World* world = new World();
ChunkController* cc = new ChunkController(world);
Window window = Window(SCR_WIDTH, SCR_HEIGHT, std::string("The Graphics Engine"), &camera, world, cc);


int main() {
	window.start();
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

	//Very hacky crosshair lmao
	std::vector<float> triangleTestvert{
		0.005f, -0.005f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		0.005f, 0.005f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		-0.005f, 0.005f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		-0.005f, -0.005f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f
	};
	std::vector<unsigned short> indices{
	0, 1, 3,
	1, 2, 3
	};
	std::vector<float> lineTest{
		5.5f, 5.5f, 5.5f, 0.5f, 0.5f, -0.5f
	};

	Mesh e = Mesh(vertices, 36);
	IndexedMesh* e3 = new IndexedMesh(indices, triangleTestvert);
	TextureMap* tm = new TextureMap(std::string("assets/textures/TextureTable.png"), 16, 16);
	
	Chunk* stone = new Chunk(glm::vec3(0.0f, -16.0f, 0.0f));
	stone->createSolidChunk();
	TextureInfo* ti = new TextureInfo();

	ChunkBuilder* stoneChunkBuilder = new ChunkBuilder(ti);
	auto start = std::chrono::high_resolution_clock::now();

	RenderInformation ri = stoneChunkBuilder->getChunkMesh(stone);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Runtime: " << duration.count() << " ms" << std::endl;
	
	tm->loadTexture(GL_RGBA);
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection;

	Shader chunkShader = Shader("LightingShader.vert", "LightingShader.frag");
	Shader lightSource = Shader("LightSourceShader.vert", "LightSourceShader.frag");
	Shader lineS = Shader("LineShader.vert", "LineShader.frag");
	Shader hud = Shader("HudShader.vert", "HudShader.frag");

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	tm->bind();

	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	const float radius = 1.0f;
	while (!glfwWindowShouldClose(window.glWindow))
	{
		world->updateWorldPosition(camera.Position);
		//Gets the current frame for input processing
		window.updateDeltaTime();
		window.processInput();
		glm::vec3 chunkPos = world->getChunkWorldPosition();

		std::cout << "X: " << world->worldPos.x << " Y: " << world->worldPos.y << "d Z: " << world->worldPos.z << " | ";
		std::cout << "X: " << chunkPos.x << " Y: " << chunkPos.y << " Z: " << chunkPos.z << std::endl;

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
		projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 400.0f);
		model = glm::mat4(1.0f);

		chunkShader.use();
		chunkShader.setMat4("model", model);
		chunkShader.setMat4("view", view);
		chunkShader.setMat4("projection", projection);
 		chunkShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		chunkShader.setVec3("lightColor", 0.95f, 0.9f, 0.65f);
		chunkShader.setVec3("lightPos", lightPos);
		chunkShader.setVec3("viewPos", camera.Position);
		cc->update();
		//Renders hacky crosshair
		hud.use();
		e3->render();
		//Preps light source cube 
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lightSource.use();
		lightSource.setMat4("model", model);
		lightSource.setMat4("view", view);
		lightSource.setMat4("projection", projection);
		e.render();

		glfwSwapBuffers(window.glWindow);
		glfwPollEvents();
	}
	std::cout << camera.Position.x << ", " << camera.Position.y << ", " << camera.Position.z << " | " << camera.Yaw << ", " << camera.Pitch << std::endl;

	glfwTerminate();
	return 0;
}

