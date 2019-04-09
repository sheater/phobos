#pragma once

#include <map>
#include <GLFW/glfw3.h>

typedef struct
{
  int key;
  bool isPressed;
} KeyboardAction;

class InputHandler
{
public:
  void bindKeyboardAction(int action, int key);
  void dispatch(GLFWwindow *window);
  bool isActionKeyPressed(int action);

private:
  std::map<int, KeyboardAction> m_keyboardActions;
};
