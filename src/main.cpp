#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "engine/Application.h"
#include "engine/Sound.h"
#include "engine/Light.h"
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

    // base light
    app->getRenderer()->addLight(new Light());

    int sceneExitCode;

    // Sound* music = static_cast<Sound *>(app->getAssetsManager()->getAsset("assets/music/theme.ogg"));

    // music->play();

    while (true)
    {
      Intro *intro = new Intro(app->getRenderer(), app->getAssetsManager(), input);

      std::cout << "Intro scene" << std::endl;
      if (app->run(intro) != INTRO_EXIT_PLAY_GAME)
        break;

      delete intro;

      std::cout << "main(): new Level" << std::endl;
      Level *level = new Level(
          "assets/levels/begin.xml",
          app->getRenderer(),
          app->getAssetsManager(),
          input);

      std::cout << "main(): app->run" << std::endl;
      sceneExitCode = app->run(level);
      delete level;

      if (sceneExitCode != LEVEL_BACK_TO_INTRO)
        break;
    }

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
