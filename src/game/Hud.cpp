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

  y += 32.0f;

  m_scoreLabel = new UILabel(uiMgr, "", glm::vec2(16.0f, y));
  m_scoreLabel->scale = 2.0f;
  uiMgr->attachNode(m_scoreLabel);
}

void Hud::update(float timeDelta)
{
  m_blinkCounter += timeDelta;

  float blinkPhase = sin(m_blinkCounter * 15.0f);

  float lifemult = glm::clamp(life / 0.25f, 0.0f, 1.0f);
  m_lifeLabel->color = glm::vec4(
      1.0f, 1.0f * lifemult, 1.0f * lifemult,
      life < 0.25 ? blinkPhase : 1.0f);
  m_lifeLabel->text = "LIFE: " + std::to_string(int(life * 100.0f)) + " %";

  float heatmult = 1.0f - glm::clamp((heat - 0.75f) / 0.25f, 0.0f, 1.0f);
  m_heatLabel->color = glm::vec4(
      1.0f, 1.0f * heatmult, 1.0f * heatmult,
      heat > 0.75f ? blinkPhase : 1.0f);
  m_heatLabel->text = "HEAT: " + std::to_string(int(heat * 100.0f)) + " %";

  m_scoreLabel->text = "SCORE: " + std::to_string(score);
}
