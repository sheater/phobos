#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "engine/Application.h"
#include "game/Level.h"
#include "game/Intro.h"
#include "game/actions.h"

int main(void)
{
  Application *app = nullptr;

  try
  {
    app = new Application(1024, 768);

    InputHandler *input = app->getInputHandler();

    input->bindKeyboardAction(PLAYER_ACTION_MOVE_UP, GLFW_KEY_UP);
    input->bindKeyboardAction(PLAYER_ACTION_MOVE_DOWN, GLFW_KEY_DOWN);
    input->bindKeyboardAction(PLAYER_ACTION_MOVE_LEFT, GLFW_KEY_LEFT);
    input->bindKeyboardAction(PLAYER_ACTION_MOVE_RIGHT, GLFW_KEY_RIGHT);
    input->bindKeyboardAction(PLAYER_ACTION_FIRE, GLFW_KEY_SPACE);

    int sceneExitCode;

    Intro *intro = new Intro(app->getRenderer(), app->getAssetsManager(), input);

    while (true)
    {
      std::cout << "Intro scene" << std::endl;
      if (app->run(intro) != INTRO_EXIT_PLAY_GAME)
        break;

      std::cout << "Level scene" << std::endl;
      Level *level = new Level(app->getRenderer(), app->getAssetsManager(), input);
      sceneExitCode = app->run(level);
      delete level;

      if (sceneExitCode != LEVEL_BACK_TO_INTRO)
        break;
    }

    delete intro;
    delete app;
  }
  catch (std::exception &ex)
  {
    std::cerr << ex.what() << std::endl;

    if (app)
      delete app;

    return -1;
  }

  return 0;
}
