#pragma once

#include "../engine/Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Background.h"
#include "Hud.h"

class Level : public Scene
{
public:
  Level(Renderer *renderer, AssetsManager *assetsMgr, InputHandler *inputHandler)
      : Scene(renderer, assetsMgr, inputHandler)
  {
    Player *player = new Player(this);
    Background *background = new Background(this);

    attachNode(player);
    attachNode(background);

    m_enemyGenerateTimer = 0.0f;

    renderCollisionHulls = true;

    m_hud = new Hud(renderer->getWidth(), renderer->getHeight(), getUIManager());

    m_hud->setScore(100);
    m_hud->setLevel(1);
    m_hud->setLife(1.0f);
    m_hud->setHeat(1.0f);
  }

  ~Level()
  {
    delete m_hud;
  }

  void update(float timeDelta)
  {
    m_enemyGenerateTimer += timeDelta;
    if (m_enemyGenerateTimer > 2.0f)
    {
      m_enemyGenerateTimer = 0.0f;
      Enemy *enemy = new Enemy(this);
      attachNode(enemy);
    }

    Scene::update(timeDelta);
  }

  inline Hud *getHud()
  {
    return m_hud;
  }

private:
  float m_enemyGenerateTimer;
  Hud *m_hud;
};
