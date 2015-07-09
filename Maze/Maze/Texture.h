#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/freeglut.h>

class Texture
{
public:
	Texture(std::string&);
	~Texture();
	void enableTexture();
	void disableTexture();
	int getWidth();
	int getHeight();
private:
	GLuint _texture;
	int _width;
	int _height;
	int _components;
	unsigned char* _image;
};
#endif