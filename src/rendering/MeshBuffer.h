#ifndef MESHBUFFER_H
#define MESHBUFFER_H
#include <glad/glad.h>
#include <vector>
#include <rendering/RenderInformation.h>
#include <atomic>
#include <rendering/Shader.h>

enum class MeshShape {
	LINE = 2,
	TRIANGLE = 3
};
struct MeshConfig {
	int size;
	bool texture;
	bool normals;
	MeshShape shape;
	MeshConfig(int size, bool texture, bool normals, MeshShape shape) {
		this->size = size;
		this->texture = texture;
		this->normals = normals;
		this->shape = shape;
	}
	MeshConfig() = default;
};
class MeshBuffer
{
private:
	unsigned int vboId;
	unsigned int vaoId;
	unsigned int eboId;
	std::vector<float> vertices;
	std::vector<unsigned short> indices;
	MeshConfig mc;
public:
	std::atomic<bool> doBind;
	MeshBuffer();
	MeshBuffer(const MeshBuffer& buffer);
	~MeshBuffer();
	void loadMesh(RenderInformation& ri, MeshConfig& config);
	void draw();
	void bind();
	bool isEmpty();
};
#endif
