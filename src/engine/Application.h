#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "AssetsManager.h"
#include "Scene.h"
#include "InputHandler.h"
#include "ParticleSystem.h"
#include "AudioEngine.h"

class Application
{
public:
  Application(unsigned int width, unsigned int height);
  ~Application();

  void onResize(GLFWwindow *window, int width, int height);
  void onMouseMove(GLFWwindow *window, double x, double y);
  void onMousePressed(GLFWwindow *window, int button, int action, int mods);
  void onKeyPressed(GLFWwindow *window, int key, int scancode, int action, int mods);

  int run(Scene *scene);

  inline Renderer *getRenderer() { return m_renderer; }
  inline AssetsManager *getAssetsManager() { return m_assetsMgr; }
  inline InputHandler *getInputHandler() { return m_inputHandler; }
  inline AudioEngine *getAudioEngine() { return m_audioEngine; }

private:
  unsigned int m_width;
  unsigned int m_height;

  GLFWwindow *m_window;
  Renderer *m_renderer;
  AssetsManager *m_assetsMgr;
  InputHandler *m_inputHandler;
  AudioEngine *m_audioEngine;
};
