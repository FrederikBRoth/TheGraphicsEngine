#ifndef SOLIDRENDERER_H
#define SOLIDRENDERER_H
#include <rendering/Shader.h>
#include <rendering/RenderInformation.h>
#include <unordered_map>
#include <rendering/MeshBuffer.h>
#include <world/WorldUtils.h>
#include <controls/Camera.h>
class SolidRenderer
{
private:
	Shader shader = Shader("LightingShader.vert", "LightingShader.frag");
public:

	void render(std::unordered_map<VectorXZ, MeshBuffer*>& meshes, Camera* camera);
};
#endif
