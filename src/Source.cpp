#pragma once
#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <rendering/Shader.h>
#include <controls/Camera.h>
#include <stb_image.h>
#include <chunk/Chunk.h>
#include <texturing/TextureMap.h>
#include <chrono>
#include <world/World.h>
#include <chunk/ChunkController.h>
#include <chunk/MeshBuilder.h>
#include <controls/LineTrace.h>
#include <default/Window.h>
#include <world/world-rendering/Renderer.h>
#include <controls/player/Player.h>
#include <gui/ScreenText.h>
#include <gui/gui-elements/InventoryGui.h>
#include <entities/collision/PhysicsHandler.h>
#include <entities/Item.h>

Camera camera(glm::vec3(-0.5f, 20.0f, 3.5f), glm::vec3(0.0f, 1.0f, 0.0f), -63.f, -18.0f);
World* world = new World();
TextureMap* tm = new TextureMap(std::string("assets/textures/TextureTable.png"), 16, 16);
MeshBuilder* mb = new MeshBuilder(world);
ChunkController* cc = new ChunkController(world, mb);
Window window = Window(SCREEN_WIDTH, SCREEN_HEIGHT, std::string("The Graphics Engine"), &camera, world, cc);
Player* player = new Player(&camera);
ScreenText* st = new ScreenText();
PhysicsHandler ph = PhysicsHandler();
std::vector<Entity> entities;
int main() {
	window.start();
	mb->ti->texture = tm;
	
	Chunk* stone = new Chunk(glm::vec3(0.0f, -16.0f, 0.0f));
	stone->createSolidChunk();
	MeshBuilder* stoneChunkBuilder = new MeshBuilder(world);
	auto start = std::chrono::high_resolution_clock::now();
	std::unordered_map <VectorXZ, Chunk*> chunks;
	chunks[tge::getKey(0, 0)] = stone;
	RenderInformation ri = stoneChunkBuilder->getChunkMesh(tge::getKey(0, 0), &chunks).solids;
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "Runtime: " << duration.count() << " ms" << std::endl;


	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 400.0f);

	Shader lightSource = Shader("LightSourceShader.vert", "LightSourceShader.frag");
	Shader lineS = Shader("LineShader.vert", "LineShader.frag");
	Shader text = Shader("TextShader.vert", "TextShader.frag");
	
	tm->loadTexture(GL_RGBA);

	st->setup("minecraft_font.ttf", text);

	glDisable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	
	glm::vec3 lightPos(1.2f, 48.0f, 2.0f);
	const float radius = 1.0f;


	Renderer* renderer = new Renderer(mb, &camera);
	InventoryGui* gui = new InventoryGui(st, player);

	while (!glfwWindowShouldClose(window.glWindow))
	{
		world->updateWorldPosition(camera.Position);
		//Gets the current frame for input processing
		window.updateDeltaTime();
		window.processInput(player);
		glm::vec3 chunkPos = world->getChunkWorldPosition();
		player->update(camera, &cc->chunkMap);
		ph.update(world->entities, cc);
		//std::cout << "X: " << world->worldPos.x << " Y: " << world->worldPos.y << "d Z: " << world->worldPos.z << " | ";
		//std::cout << "X: " << camera.relativeVelocity.x << " Y: " << camera.relativeVelocity.y << " Z: " << camera.relativeVelocity.z << std::endl;
		//std::cout << "X: " << camera.Position.x << " Y: " << camera.Position.y << "d Z: " << camera.Position.z << std::endl;
		//std::cout << world->entities.size() << std::endl;
		std::cout << camera.Yaw << std::endl;
		
		float camX = sin((float)glfwGetTime()) * radius;
		float camZ = cos((float)glfwGetTime()) * radius;

		lightPos = glm::vec3(camX, 0.0f, camZ);
		lightPos = glm::vec3(5.0f, 10.0f, 5.0f);
		//Clears the screen for the new frame render
		glClearColor(0.44f, 0.73f, 0.83f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Binds the normal cube
		//Sets projection matrices

		cc->chunkGeneration();
		renderer->renderAll();
		cc->chunkDegeneration();
	
		glm::mat4 projection2 = glm::ortho(0.0f, (float)SCREEN_WIDTH, 0.0f, (float)SCREEN_HEIGHT);
		text.use();
		text.setMat4("projection", projection2);
		float fps = (1.0f / window.getDeltaTime());
		//Crosshair
		st->renderText("><", SCREEN_WIDTH / 2 - 13.4f, SCREEN_HEIGHT / 2 - 11, 0.5f, glm::vec3(1, 0, 0));
		
		std::stringstream ss;
		ss << "FPS: " << std::fixed << std::setprecision(2) << fps;
		st->renderText(ss.str(), 1400.0f, 800.0f, 1.0f, glm::vec3(1, 0, 0));
		gui->renderGui();

		glfwSwapBuffers(window.glWindow);
		glfwPollEvents();
	}
	std::cout << camera.Position.x << ", " << camera.Position.y << ", " << camera.Position.z << " | " << camera.Yaw << ", " << camera.Pitch << std::endl;

	glfwTerminate();
	return 0;
}

