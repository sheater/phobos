#pragma once

#include <OpenGL/gl.h>
#include <glm/glm.hpp>

#include "GpuProgram.h"
#include "VertexBuffer.h"
#include "Texture.h"

class Renderer
{
public:
  Renderer();
  ~Renderer();

  void useBaseProgram(const glm::mat4x4 &transform, Material* material = nullptr);
  void setViewport(unsigned int width, unsigned int height);

  VertexBuffer *createVertexBuffer(Geometry *geometry);
  Texture *createTexture(unsigned int width, unsigned int height, void *pixels);

  void clearBuffers();
  void flush();

private:
  void checkError();

  unsigned int m_width;
  unsigned int m_height;

  std::vector<VertexBuffer *> m_vertexBuffers;
  std::vector<Texture *> m_textures;

  GpuProgram *m_baseProgram;
  glm::mat4x4 m_projectionMatrix;
  glm::mat4x4 m_viewMatrix;
};
