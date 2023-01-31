#ifndef TEXTURECOORD_H
#define TEXTURECOORD_H
struct TextureCoord {
	float xCoord;
	float yCoord;
	TextureCoord();
	TextureCoord(float xCoord, float yCoord);
};

struct TextureCoords {
	TextureCoord topleft;
	TextureCoord topright;
	TextureCoord bottomleft;
	TextureCoord bottomright;
	TextureCoords(TextureCoord topleft, TextureCoord topright, TextureCoord bottomleft, TextureCoord bottomright);
	TextureCoords();
};

#endif // !TEXTURECOORD_H
