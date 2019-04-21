#pragma once

#include <glm/glm.hpp>

class UIManager;

class UINode
{
public:
  UINode(const glm::vec2 &initialPosition, UIManager *uiMgr);

  virtual void render();

  glm::vec2 position;
  glm::vec2 size;
  glm::vec4 color;
  bool visible;

protected:
  UIManager *m_uiMgr;
};
