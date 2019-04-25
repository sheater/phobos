#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <glm/glm.hpp>

#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(Geometry *geometry, Renderer *renderer)
    : m_renderer(renderer)
{
  m_numVertices = geometry->positions.size();
  if (!m_numVertices)
  {
    throw std::runtime_error("Unable to create RenderObject from empty position buffer");
  }

  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  unsigned int positionsSize = sizeof(glm::vec3) * geometry->positions.size();
  unsigned int normalsSize = sizeof(glm::vec3) * geometry->normals.size();
  unsigned int texcoordsSize = sizeof(glm::vec2) * geometry->texcoords.size();
  unsigned int totalSize = positionsSize + normalsSize + texcoordsSize;

  GLuint vbo, ibo = 0;

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glBufferData(GL_ARRAY_BUFFER, totalSize, 0, GL_STATIC_DRAW);

  glBufferSubData(GL_ARRAY_BUFFER, 0, positionsSize, &geometry->positions[0]);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  if (!geometry->normals.empty())
  {
    if (geometry->normals.size() != m_numVertices)
      throw new std::runtime_error("Number of normals does not match");

    glBufferSubData(GL_ARRAY_BUFFER, positionsSize, normalsSize, &geometry->normals[0]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)positionsSize);
    glEnableVertexAttribArray(1);
  }

  if (!geometry->texcoords.empty())
  {
    if (geometry->texcoords.size() != m_numVertices)
      throw new std::runtime_error("Number of texcoords does not match");

    glBufferSubData(GL_ARRAY_BUFFER, positionsSize + normalsSize, texcoordsSize, &geometry->texcoords[0]);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(positionsSize + normalsSize));
    glEnableVertexAttribArray(2);
  }

  m_numIndices = geometry->indices.size();

  if (!geometry->indices.empty())
  {
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * geometry->indices.size(), &geometry->indices[0], GL_STATIC_DRAW);
  }

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glDeleteBuffers(1, &vbo);
  if (ibo)
  {
    glDeleteBuffers(1, &ibo);
  }
}

VertexBuffer::~VertexBuffer()
{
  glDeleteVertexArrays(1, &m_vao);
}

void VertexBuffer::render()
{
  glBindVertexArray(m_vao);
  if (m_numIndices)
  {
    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, (void *)0);
  }
  else
  {
    glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
  }
}
