#pragma once

#include "../engine/Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Background.h"

class Level : public Scene
{
public:
  Level(Renderer *renderer, AssetsManager *assetsMgr, InputHandler *inputHandler)
      : Scene(renderer, assetsMgr, inputHandler)
  {
    // Scene *scene = app->getScene();
    // InputHandler *input = app->getInputHandler();

    Player *player = new Player(this);
    Background *background = new Background(this);

    attachNode(player);
    attachNode(background);
  }

  void update(float timeDelta)
  {
    Scene::update(timeDelta);
  }
};
