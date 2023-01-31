#ifndef INDEXMESH_H
#define INDEXMESH_H
#include <entities/IMesh.h>
#include <rendering/IndexBuffer.h>
#include <rendering/RenderInformation.h>

class IndexedMesh : public IMesh
{
public:
	RenderInformation ri;
	IndexBuffer* ebo;
	IndexedMesh(std::vector<unsigned short> indices, std::vector<float> vertices);
	IndexedMesh(RenderInformation &ri);

	~IndexedMesh();
	virtual void render() override;

};
#endif