#pragma once

#include "../engine/UIManager.h"
#include "../engine/UILabel.h"
#include "../engine/UIImage.h"

class Hud
{
public:
  Hud(unsigned int width, unsigned int height, UIManager *uiMgr);

  unsigned int score;
  float life = 1.0f;
  float heat = 1.0f;

  void update(float timeDelta);

private:
  float m_blinkCounter = 0.0f;

  UIManager *m_uiMgr;

  UIImage* m_lifeImage;
  UILabel* m_lifeLabel;
  UIImage* m_heatImage;
  UILabel* m_heatLabel;

  UILabel* m_scoreLabel;
};
