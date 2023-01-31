#ifndef RENDERER_H
#define RENDERER_H
#include <chunk/MeshBuilder.h>
#include <world/world-rendering/SolidRenderer.h>
#include <world/world-rendering/Transparentrenderer.h>

class Renderer {
private:
	Camera* camera;
	MeshBuilder* meshes;
	SolidRenderer* sr;
	TransparentRenderer* tr;
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
public:
	Renderer(MeshBuilder* meshes, Camera* camera);
	void renderAll();
};
#endif // !RENDERER_H
