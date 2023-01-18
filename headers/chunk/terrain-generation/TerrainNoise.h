

#ifndef TERRAINNOISE_H
#define TERRAINNOISE_H
#include <vector>
#include <perlinNoise/PerlinNoise.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <world/Constants.h>
#include <world/WorldUtils.h>
class TerrainNoise {
private:
	siv::PerlinNoise perlin;
public:
	TerrainNoise();
	TerrainNoise(unsigned int seed);
	std::vector<int> generateNoiseMap(glm::vec3& position, int magnitude, double multiplier);

};

#endif