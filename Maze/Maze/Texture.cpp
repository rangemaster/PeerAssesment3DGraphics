#include "stdafx.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include "stb_image.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <GL/freeglut.h>

Texture::Texture(std::string& name)
{
	printf("NAME: %s", name.c_str());
	glGenTextures(1, &_texture);
	_image = stbi_load(name.c_str(), &_width, &_height, &_components, 4);
}

Texture::~Texture()
{
	stbi_image_free(_image);
}

int Texture::getWidth()
{
	return this->_width;
}

int Texture::getHeight()
{
	return this->_height;
}

/*
* Enables the texture so it used by opengl
*/
void Texture::enableTexture()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _texture);

	/* TODO This code copies the image every time may need
	*		to be optimized
	*/
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _image);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Texture::disableTexture()
{
	//glDisable(GL_BLEND);
	glDeleteTextures(1, &_texture);
}