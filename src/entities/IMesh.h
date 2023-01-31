#ifndef IMESH_H
#define IMESH_H
#include <rendering/VertexArray.h>
class IMesh {
public:
	VertexArray* vao;
	virtual void render() = 0;
};

#endif // !IMESH_H
