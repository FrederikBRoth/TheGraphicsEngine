#ifndef RENDERER_H
#define RENDERER_H
#include <chunk/MeshBuilder.h>
#include <world/world-rendering/SolidRenderer.h>
#include <world/world-rendering/Transparentrenderer.h>
#include <world/world-rendering/ItemRenderer.h>

class Renderer {
private:
	Camera* camera;
	MeshBuilder* meshes;
	SolidRenderer* sr;
	TransparentRenderer* tr;
	ItemRenderer* ir;

public:
	Renderer(MeshBuilder* meshes, Camera* camera);
	void renderAll();
};
#endif // !RENDERER_H
