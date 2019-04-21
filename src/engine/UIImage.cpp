#include "UIImage.h"
#include "UIManager.h"
#include "AssetsManager.h"
#include "Texture.h"

UIImage::UIImage(
    UIManager *uiMgr,
    const std::string &path,
    const glm::vec2 &initialPosition)
    : UINode(initialPosition, uiMgr)
{
  m_texture = static_cast<Texture *>(uiMgr->getAssetsManager()->getAsset(path));
}

void UIImage::render()
{
  m_uiMgr->setTranslation(position)
      ->setSize(size)
      ->setColor(color);
  m_texture->bind();
  m_uiMgr->renderQuad();
}
