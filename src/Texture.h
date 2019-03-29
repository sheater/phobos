#pragma once

#include <OpenGL/gl.h>
#include <string>

#include "Asset.h"

class Texture : public Asset
{
public:
  Texture(unsigned int width, unsigned int height, void *pixels);
  ~Texture();

  void bind();

private:
  GLuint m_id;
};
