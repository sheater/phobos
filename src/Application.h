#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "AssetsManager.h"
#include "Scene.h"

class Application
{
public:
  Application(unsigned int width, unsigned int height);
  ~Application();

  void frame(float timeDelta);

  void onResize(GLFWwindow *window, int width, int height);
  void onMouseMove(GLFWwindow *window, double x, double y);
  void onMousePressed(GLFWwindow *window, int button, int action, int mods);
  void onKeyPressed(GLFWwindow *window, int key, int scancode, int action, int mods);

private:
  unsigned int m_width;
  unsigned int m_height;

  Renderer* m_renderer;
  AssetsManager* m_assetsMgr;
  Scene* m_scene;
};
