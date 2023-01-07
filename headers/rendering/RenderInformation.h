#ifndef RENDERINFORMATION_H
#define RENDERINFORMATION_H
#include <vector>
struct RenderInformation {
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
};
#endif // !RENDERINFORMATION_H
