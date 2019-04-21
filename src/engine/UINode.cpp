#include "UINode.h"
#include "UIManager.h"

UINode::UINode(const glm::vec2 &initialPosition, UIManager *uiMgr)
    : position(initialPosition),
      visible(true),
      color(glm::vec4(1.0f)),
      size(1.0f),
      m_uiMgr(uiMgr)
{
}

void UINode::render()
{
}
