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

  inline unsigned int getWidth() { return m_width; }
  inline unsigned int getHeight() { return m_height; }

private:
  unsigned int m_width;
  unsigned int m_height;
  GLuint m_id;
};
