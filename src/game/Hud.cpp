#include "Hud.h"

Hud::Hud(unsigned int width, unsigned int height, UIManager *uiMgr)
    : m_uiMgr(uiMgr)
{
  float y = 16.0f;

  m_lifeImage = new UIImage(uiMgr, "assets/textures/heart.png", glm::vec2(14.0f, y - 2.0f));
  m_lifeImage->size = glm::vec2(20.0f);
  m_lifeLabel = new UILabel(uiMgr, "", glm::vec2(40.0f, y));
  m_lifeLabel->scale = 2.0f;
  uiMgr
      ->attachNode(m_lifeImage)
      ->attachNode(m_lifeLabel);

  y += 32.0f;

  m_heatImage = new UIImage(uiMgr, "assets/textures/spark.png", glm::vec2(16.0f, y));
  m_heatImage->size = glm::vec2(16.0f);
  m_heatLabel = new UILabel(uiMgr, "", glm::vec2(40.0f, y));
  m_heatLabel->scale = 2.0f;
  uiMgr
      ->attachNode(m_heatImage)
      ->attachNode(m_heatLabel);

  // m_scoreLabel = new UILabel(uiMgr, "", glm::vec2(16.0f, startY));
  // m_scoreLabel->scale = 2.0f;
  // uiMgr->attachNode(m_scoreLabel);

  // m_levelLabel = new UILabel(uiMgr, "", glm::vec2(16.0f, startY + 3 * labelHeight));
  // m_levelLabel->scale = 2.0f;
  // uiMgr->attachNode(m_levelLabel);
}

void Hud::setScore(unsigned int score)
{
  // m_scoreLabel->text = "SCORE: " + std::to_string(score);
}

void Hud::setLife(float life)
{
  float mult = glm::clamp(life / 0.25f, 0.0f, 1.0f);
  m_lifeLabel->color = glm::vec4(1.0f, 1.0f * mult, 1.0f * mult, 1.0f);
  m_lifeLabel->text = "LIFE: " + std::to_string(int(life * 100.0f)) + " %";
}

void Hud::setHeat(float heat)
{
  float mult = 1.0f - glm::clamp((heat - 0.75f) / 0.25f, 0.0f, 1.0f);
  m_heatLabel->color = glm::vec4(1.0f, 1.0f * mult, 1.0f * mult, 1.0f);
  m_heatLabel->text = "HEAT: " + std::to_string(int(heat * 100.0f)) + " %";
}

void Hud::setLevel(unsigned int level)
{
  // m_levelLabel->text = "LEVEL: " + std::to_string(level);
}
