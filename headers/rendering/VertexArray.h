#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H
#include <rendering/VertexBuffer.h>

class VertexArray
{
public:
	unsigned int ID;
	VertexBuffer* vbo;
	VertexArray(float* vertices, int triangleCount);
	~VertexArray();
	void init(int size);
	void bind();

};
#endif // !VERTEXARRAY_H
