#include <chunk/terrain-generation/PerlinNoise.h>

PerlinNoise::PerlinNoise()
{
	siv::PerlinNoise::seed_type seed = 123456u;
	perlin = siv::PerlinNoise(seed);
}

PerlinNoise::PerlinNoise(unsigned int seed)
{
	perlin = siv::PerlinNoise(seed);
}

std::vector<int> PerlinNoise::generateNoiseMap(glm::vec3& position, int magnitude, double multiplier)
{
	std::vector<int> noiseMap;
	for (int z = position.z; z < position.z + CHUNKSIZE_Z; z++) {
		for (int x = position.x; x < position.x + CHUNKSIZE_X; x++) {
			double n = perlin.noise2D((x * multiplier), (z * multiplier));
			noiseMap.push_back(floor(magnitude * n));
		}
	}
	return noiseMap;
}
