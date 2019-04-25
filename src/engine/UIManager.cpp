#include <GL/glew.h>

#include "UIManager.h"
#include "Renderer.h"

UIManager::UIManager(Renderer *renderer, AssetsManager *assetsMgr)
    : m_renderer(renderer), m_assetsMgr(assetsMgr)
{
  createArrayObject();

  m_font = new Font(assetsMgr, "assets/textures/font.png");
  m_gpuProgram = nullptr;
}

void UIManager::createArrayObject()
{
  glm::vec2 positions[] = {
      glm::vec2{0.0f, 1.0f},
      glm::vec2{1.0f, 1.0f},
      glm::vec2{1.0f, 0.0f},
      glm::vec2{0.0f, 0.0f},
  };

  glm::vec2 texcoords[] = {
      glm::vec2{0.0f, 0.0f},
      glm::vec2{1.0f, 0.0f},
      glm::vec2{1.0f, 1.0f},
      glm::vec2{0.0f, 1.0f},
  };

  GLuint indices[] = {0, 1, 2, 2, 3, 0};

  glGenVertexArrays(1, &m_quadVao);
  glBindVertexArray(m_quadVao);

  GLuint vbo, ibo;

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  unsigned int positionsSize = sizeof(positions);
  unsigned int texcoordsSize = sizeof(texcoords);
  unsigned int totalSize = positionsSize + texcoordsSize;
  glBufferData(GL_ARRAY_BUFFER, totalSize, 0, GL_STATIC_DRAW);

  // vertex positions
  glBufferSubData(GL_ARRAY_BUFFER, 0, positionsSize, &positions[0]);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

  // texture coords
  glBufferSubData(GL_ARRAY_BUFFER, positionsSize, texcoordsSize, &texcoords[0]);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(positionsSize));

  // indices
  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ibo);
}

UIManager::~UIManager()
{
  for (
      std::vector<UINode *>::iterator it = m_nodes.begin();
      it != m_nodes.end();
      it++)
  {
    delete *it;
  }
}

UIManager *UIManager::attachNode(UINode *node)
{
  m_nodes.push_back(node);

  return this;
}

UIManager *UIManager::releaseNode(UINode *node)
{
  std::vector<UINode *>::iterator it = std::find(m_nodes.begin(), m_nodes.end(), node);
  if (it != m_nodes.end())
  {
    delete *it;
    m_nodes.erase(it);
  }

  return this;
}

void UIManager::render()
{
  m_gpuProgram = m_renderer->bindGpuProgram(GPU_PROGRAM_UI);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  for (
      std::vector<UINode *>::iterator it = m_nodes.begin();
      it != m_nodes.end();
      it++)
  {
    if (!(*it)->visible)
      continue;

    (*it)->render();
  }

  glDisable(GL_BLEND);
}

void UIManager::renderQuad()
{
  glBindVertexArray(m_quadVao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0);
  glBindVertexArray(0);
}

UIManager *UIManager::setTranslation(const glm::vec2 &translation)
{
  m_gpuProgram->setUniformVec2("position", translation);
  return this;
}

UIManager *UIManager::setSize(const glm::vec2 &size)
{
  m_gpuProgram->setUniformVec2("size", size);
  return this;
}

UIManager *UIManager::setColor(const glm::vec4 &color)
{
  m_gpuProgram->setUniformVec4("color", color);
  return this;
}
