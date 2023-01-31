#ifndef MESH_H
#define MESH_H
#include <entities/IMesh.h>
#include <rendering/IndexBuffer.h>

class Mesh : public IMesh
{
public:
	int triangleCount;
	Mesh(std::vector<float> vertices, int triangleCount);
	~Mesh();
	virtual void render() override;
};
#endif
