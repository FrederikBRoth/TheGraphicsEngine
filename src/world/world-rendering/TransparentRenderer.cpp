#include <world/world-rendering/TransparentRenderer.h>
void TransparentRenderer::render(std::unordered_map<VectorXZ, MeshBuffer*>& meshes, Camera* camera)
{
	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 400.0f);
	glm::mat4 model = glm::mat4(1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	shader.use();
	shader.setMat4("model", model);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
	shader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
	shader.setVec3("lightColor", 0.95f, 0.9f, 0.65f);
	shader.setVec3("lightPos", glm::vec3(5.0f, 10.0f, 5.0f));
	shader.setVec3("viewPos", camera->Position);
	for (auto& chunkMesh : meshes) {
		if (!chunkMesh.second->isEmpty()) {
			if (chunkMesh.second->doBind) {
				chunkMesh.second->bind();
				chunkMesh.second->doBind = { false };
			}
			chunkMesh.second->draw();
		}
	}
}
