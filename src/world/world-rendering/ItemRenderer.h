#ifndef ITEMRENDERER_H
#define ITEMRENDERER_H
#include <rendering/Shader.h>
#include <rendering/RenderInformation.h>
#include <unordered_map>
#include <rendering/MeshBuffer.h>
#include <world/WorldUtils.h>
#include <controls/Camera.h>
#include <entities/Entity.h>

class ItemRenderer
{
private:
	Shader shader = Shader("ItemShader.vert", "ItemShader.frag");
public:
	void render(std::vector<Entity*> meshes, Camera* camera);
};
#endif // !ITEMRENDERER_H
