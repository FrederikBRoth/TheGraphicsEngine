#include <world/world-rendering/Renderer.h>

Renderer::Renderer(MeshBuilder* meshes, Camera* camera)
{
	this->camera = camera;
	this->meshes = meshes;
	sr = new SolidRenderer();
	tr = new TransparentRenderer();
	ir = new ItemRenderer();
}


void Renderer::renderAll()
{
	meshes->ti->texture->bind();
	sr->render(meshes->chunkMap, camera);
	tr->render(meshes->waterMap, camera);
	ir->render(meshes->world->entities, camera);
}
