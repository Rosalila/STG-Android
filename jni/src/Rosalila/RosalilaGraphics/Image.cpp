#include "RosalilaGraphics/RosalilaGraphics.h"

Image::Image()
{
    width=-1;
    height=-1;
}

int Image::getWidth()
{
    return width;
}
int Image::getHeight()
{
    return height;
}

GLuint Image::getTexture()
{
    return texture;
}

void Image::setTexture(GLuint texture)
{
    this->texture=texture;
}

void Image::setWidth(int width)
{
    this->width=width;
}
void Image::setHeight(int height)
{
    this->height=height;
}

Image::~Image()
{
    glDeleteTextures( 1, &texture );
}

void Image::setSdlTexture(SDL_Texture *sdl_texture)
{
	this->sdl_texture=sdl_texture;
}
