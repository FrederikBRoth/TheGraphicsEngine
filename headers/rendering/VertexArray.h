#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H
#include <rendering/VertexBuffer.h>
//more to add whenever i learn more about other masks
enum Shape {
	LINE = 2,
	TRIANGLE = 3
};
struct VertexArrayConfig {
	int size;
	bool texture;
	bool normals;
	Shape shape;
	VertexArrayConfig(int size, bool texture, bool normals, Shape shape) {
		this->size = size;
		this->texture = texture;
		this->normals = normals;
		this->shape = shape;
	}
};

class VertexArray
{
public:
	unsigned int ID;
	VertexBuffer* vbo;
	VertexArray(std::vector<float> vertices);
	~VertexArray();
	void init(VertexArrayConfig config);
	void bind();

};
#endif // !VERTEXARRAY_H
