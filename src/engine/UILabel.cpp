#include "UILabel.h"
#include "UIManager.h"
#include "AssetsManager.h"

UILabel::UILabel(
    UIManager *uiMgr,
    const std::string &initialText,
    const glm::vec2 &initialPosition = glm::vec2(1.0f))
    : text(initialText),
      scale(1.0f),
      UINode(initialPosition, uiMgr)
{
}

UILabel::~UILabel()
{
}

void UILabel::render()
{
  Font *font = m_uiMgr->getFont();
  glm::vec2 cursor(0.0f);

  font->bind();
  m_uiMgr->setColor(color);

  for (
      std::string::const_iterator it = text.begin();
      it != text.end();
      it++)
  {
    glm::vec2 glyphSize = font->getGlyphSize(*it);
    m_uiMgr
        ->setTranslation(position + cursor)
        ->setSize(glyphSize * scale);
    font->renderGlyph(*it);
    cursor.x += glyphSize.x * scale;
  }
}

unsigned int UILabel::getWidth()
{
  unsigned int w = 0;
  Font *font = m_uiMgr->getFont();

  for (
      std::string::const_iterator it = text.begin();
      it != text.end();
      it++)
  {
    w += font->getGlyphSize(*it).x * scale;
  }

  return w;
}
