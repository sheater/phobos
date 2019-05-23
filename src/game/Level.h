#pragma once

#include <tinyxml2.h>

#include "../engine/Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Background.h"
#include "Hud.h"

#define LEVEL_BACK_TO_INTRO 1

using namespace tinyxml2;

class Level : public Scene
{
public:
  Level(
      const std::string &path,
      Renderer *renderer,
      AssetsManager *assetsMgr,
      InputHandler *inputHandler,
      AudioEngine *audioEngine);

  ~Level();

  void update(float timeDelta);

  inline Hud *getHud()
  {
    return m_hud;
  }

private:
  void loadLevel(const std::string &path);
  void parseRowElement(XMLElement *element);

  float m_enemyGenerateTimer;
  Player *m_player;
  Hud *m_hud;
};
