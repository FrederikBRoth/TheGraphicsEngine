#include <rendering/MeshBuffer.h>
MeshBuffer::MeshBuffer() {
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);
	glGenBuffers(1, &eboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
}

MeshBuffer::~MeshBuffer()
{
	glDeleteBuffers(1, &vboId);
	glDeleteVertexArrays(1, &vaoId);
}

void MeshBuffer::loadMesh(RenderInformation& ri, MeshConfig& config)
{
	vertices = ri.vertices;
	indices = ri.indices;
	mc = config;
	doBind = { true };
}

void MeshBuffer::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	int index = 0;
	glBindVertexArray(vaoId);
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, mc.size * sizeof(float), (void*)0);
	glEnableVertexAttribArray(index);
	index++;
	if (mc.normals) {
		glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, mc.size * sizeof(float), (void*)((index * 3) * sizeof(float)));
		glEnableVertexAttribArray(index);
		index++;
	}
	if (mc.texture) {
		glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, mc.size * sizeof(float), (void*)((index * 3) * sizeof(float)));
		glEnableVertexAttribArray(index);
		index++;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
	doBind = { false };
}
MeshBuffer::MeshBuffer(const MeshBuffer& buffer)
{
	vboId = buffer.vboId;
	vaoId = buffer.vaoId;
	eboId = buffer.eboId;
	mc = buffer.mc;
}
void MeshBuffer::draw()
{
	glBindVertexArray(vaoId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, 0);

}



