#pragma once

#include "../engine/UIManager.h"
#include "../engine/UILabel.h"
#include "../engine/UIImage.h"

class Hud
{
public:
  Hud(unsigned int width, unsigned int height, UIManager *uiMgr);

  void setScore(unsigned int score);
  void setLife(float life);
  void setHeat(float heat);
  void setLevel(unsigned int level);

private:
  UIManager *m_uiMgr;
  

  UIImage* m_lifeImage;
  UILabel* m_lifeLabel;
  UIImage* m_heatImage;
  UILabel* m_heatLabel;

  UILabel* m_scoreLabel;
  UILabel* m_levelLabel;
};
