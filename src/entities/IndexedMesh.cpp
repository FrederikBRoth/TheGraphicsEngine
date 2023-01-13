#include <entities/IndexedMesh.h>
IndexedMesh::IndexedMesh(std::vector<unsigned short> indices, std::vector<float> vertices)
{
	this->vao = new VertexArray(vertices);
	this->ebo = new IndexBuffer(indices);
	this->ebo->init();
	this->vao->init(8);

}

IndexedMesh::IndexedMesh(RenderInformation &ri)
{
	this->ri = ri;
	this->vao = new VertexArray(ri.vertices);
	this->ebo = new IndexBuffer(ri.indices);
	this->ebo->init();
	this->vao->init(8);
}

IndexedMesh::~IndexedMesh()
{
	delete this->vao;
	delete this->ebo;
}

void IndexedMesh::render()
{
	this->vao->bind();
	this->ebo->bind();
	// Draw the triangles !
	glDrawElements(GL_TRIANGLES, this->ebo->indices.size(), GL_UNSIGNED_SHORT, 0);
}
