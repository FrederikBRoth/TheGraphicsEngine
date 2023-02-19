#ifndef SCREENTEXT_H
#define SCREENTEXT_H
#include <iostream>
#include <helpers/RootDir.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <glad/glad.h>
#include <rendering/Shader.h>

#include <ft2build.h>
#include FT_FREETYPE_H  
struct Character {
    unsigned int textureID;  // ID handle of the glyph texture
    glm::ivec2   size;       // Size of glyph
    glm::ivec2   bearing;    // Offset from baseline to left/top of glyph
    unsigned int advance;    // Offset to advance to next glyph
};

class ScreenText
{
public:
    unsigned int vao, vbo;
    std::map<char, Character> characters;
	void setup(std::string fontName);
    void renderText(Shader& s, std::string text, float x, float y, float scale, glm::vec3 color);
};

#endif // !SCREENTEXT_H
