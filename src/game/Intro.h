#pragma once

#include "../engine/Scene.h"
#include "../engine/UILabel.h"

#include "actions.h"
#include "Background.h"
#include "Introship.h"

#define INTRO_EXIT_PLAY_GAME 1

class Intro : public Scene
{
public:
  Intro(Renderer *renderer, AssetsManager *assetsMgr, InputHandler *inputHandler)
      : Scene(renderer, assetsMgr, inputHandler)
  {
    Background *background = new Background(this);
    Introship *ship = new Introship(this);

    attachNode(background);
    attachNode(ship);

    UIManager *uiMgr = getUIManager();

    UILabel *label = new UILabel(uiMgr, "Press spacebar to start");
    label->scale = 3.0f;
    label->position = glm::vec2(
        (renderer->getWidth() - label->getWidth()) * 0.5f,
        renderer->getHeight() - 100.0f);
    uiMgr->attachNode(label);
  }

  void update(float timeDelta)
  {
    InputHandler *input = getInputHandler();

    std::cout << "up";
    if (input->isActionKeyPressed(PLAYER_ACTION_FIRE)) {
      std::cout << "Exit intro" << std::endl;
      exitScene(INTRO_EXIT_PLAY_GAME);
    }

    Scene::update(timeDelta);
  }
};
