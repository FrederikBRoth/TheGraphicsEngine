#include  <texturing/TextureCoords.h>
TextureCoords::TextureCoords(TextureCoord topleft, TextureCoord topright, TextureCoord bottomleft, TextureCoord bottomright)
{
	this->topleft = topleft;
	this->topright = topright;
	this->bottomleft = bottomleft;
	this->bottomright = bottomright;
}

TextureCoords::TextureCoords()
{
	this->topleft = TextureCoord();
	this->topright = TextureCoord();
	this->bottomleft = TextureCoord();
	this->bottomright = TextureCoord();
}


TextureCoord::TextureCoord()
{
	this->xCoord = 0.0f;
	this->yCoord = 0.0f;
}

TextureCoord::TextureCoord(float xCoord, float yCoord)
{
	this->xCoord = xCoord;
	this->yCoord = yCoord;
}
