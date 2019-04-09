#include "InputHandler.h"

void InputHandler::bindKeyboardAction(int action, int key)
{
  m_keyboardActions.insert(std::pair<int, KeyboardAction>(action, {key, false}));
}

void InputHandler::dispatch(GLFWwindow *window)
{
  int state;

  for (
      std::map<int, KeyboardAction>::iterator it = m_keyboardActions.begin();
      it != m_keyboardActions.end();
      it++)
  {
    state = glfwGetKey(window, it->second.key);
    it->second.isPressed = state == GLFW_PRESS;
  }
}

bool InputHandler::isActionKeyPressed(int action)
{
  std::map<int, KeyboardAction>::iterator it = m_keyboardActions.find(action);
  if (it == m_keyboardActions.end())
  {
    return false;
  }

  return it->second.isPressed;
}
