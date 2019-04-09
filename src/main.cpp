#include <glm/gtc/matrix_transform.hpp>

#include "engine/Application.h"
#include "game/Level.h"

int main(void)
{
  Application *app = nullptr;

  try
  {
    app = new Application(1024, 768);

    InputHandler* input = app->getInputHandler();

    input->bindKeyboardAction(PLAYER_ACTION_MOVE_UP, GLFW_KEY_UP);
    input->bindKeyboardAction(PLAYER_ACTION_MOVE_DOWN, GLFW_KEY_DOWN);
    input->bindKeyboardAction(PLAYER_ACTION_MOVE_LEFT, GLFW_KEY_LEFT);
    input->bindKeyboardAction(PLAYER_ACTION_MOVE_RIGHT, GLFW_KEY_RIGHT);
    input->bindKeyboardAction(PLAYER_ACTION_FIRE, GLFW_KEY_SPACE);

    Level* level = new Level(app->getRenderer(), app->getAssetsManager(), input);

    app->run(level);

    delete level;
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
