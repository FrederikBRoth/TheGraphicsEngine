#ifndef INDEXMESH_H
#define INDEXMESH_H
#include <entities/IMesh.h>
#include <rendering/IndexBuffer.h>
#include <rendering/RenderInformation.h>

class IndexedMesh : public IMesh
{
public:
	IndexBuffer* ebo;
	IndexedMesh(std::vector<unsigned int> indices, std::vector<float> vertices);
	IndexedMesh(RenderInformation ri);

	~IndexedMesh();
	virtual void render() override;

};
#endif
