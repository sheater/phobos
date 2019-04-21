#pragma once

#include <string>

#include "UINode.h"

class Texture;
class UIManager;

class UIImage : public UINode
{
public:
  UIImage(
      UIManager *uiMgr,
      const std::string &path,
      const glm::vec2 &initialPosition);

  void render();

private:
  Texture *m_texture;
};
