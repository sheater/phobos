#pragma once

#include "UINode.h"
#include "Font.h"

class UILabel : public UINode
{
public:
  UILabel(
      UIManager *uiMgr,
      const std::string &initialText,
      const glm::vec2 &initialPosition = glm::vec2(0.0f));
  ~UILabel();

  void render();
  unsigned int getWidth();

  float scale;
  std::string text;
};
