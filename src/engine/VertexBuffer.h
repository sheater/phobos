#pragma once

#include <OpenGL/gl.h>

#include "Geometry.h"
#include "Material.h"

class Renderer;

class VertexBuffer
{
public:
  void render(const glm::mat4 &transformMatrix, Material *material = nullptr);

private:
  friend class Renderer;

  VertexBuffer(Geometry *geometry, Renderer *renderer);
  ~VertexBuffer();

  unsigned int m_numVertices;
  unsigned int m_numIndices;
  GLuint m_vao;

  Renderer *m_renderer;
};
