#ifndef TRANSRENDERER_H
#define TRANSRENDERER_H
#include <rendering/Shader.h>
#include <rendering/RenderInformation.h>
#include <unordered_map>
#include <rendering/MeshBuffer.h>
#include <world/WorldUtils.h>
#include <controls/Camera.h>
class TransparentRenderer
{
private:
	Shader shader = Shader("WaterTexture.vert", "WaterTexture.frag");
public:

	void render(std::unordered_map<VectorXZ, MeshBuffer*>& meshes, Camera* camera);
};
#endif