#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <iostream>
#include <time.h>

#include "Application.h"
#include "ColladaLoader.h"
#include "TextureLoader.h"
#include "AudioEngine.h"
#include "VorbisLoader.h"
#include "WaveLoader.h"

void on_resize(GLFWwindow *window, int width, int height);
void on_mouse_move(GLFWwindow *window, double x, double y);
void on_mouse_pressed(GLFWwindow *window, int button, int action, int mods);
void on_key_pressed(GLFWwindow *window, int key, int scancode, int action, int mods);
void error_callback(int error, const char *description);
void fix_render_on_mac(GLFWwindow *window);

Application::Application(unsigned int width, unsigned int height)
    : m_width(width), m_height(height)
{
  if (!glfwInit())
  {
    throw std::runtime_error("Could not initialize GLFW!");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwSetErrorCallback(error_callback);

  m_window = glfwCreateWindow(m_width, m_height, "Phobos", NULL, NULL);
  if (!m_window)
  {
    glfwTerminate();
    throw std::runtime_error("Could not create a window!");
  }

  glfwMakeContextCurrent(m_window);
  glfwSwapInterval(1);

  const char *openGLVersion = reinterpret_cast<const char *>(glGetString(GL_VERSION));
  std::cout << "OpenGL version: " << openGLVersion << std::endl;

  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    glfwTerminate();
    throw std::runtime_error("Could not create a glew!");
  }

  m_renderer = new Renderer(width, height);

  m_assetsMgr = new AssetsManager(m_renderer);
  m_assetsMgr->addLoader(new ColladaLoader());
  m_assetsMgr->addLoader(new TextureLoader());
  m_assetsMgr->addLoader(new VorbisLoader());
  m_assetsMgr->addLoader(new WaveLoader());

  m_inputHandler = new InputHandler();
  m_audioEngine = new AudioEngine();

  glfwSetWindowUserPointer(m_window, this);
  glfwSetWindowSizeCallback(m_window, on_resize);
  glfwSetCursorPosCallback(m_window, on_mouse_move);
  glfwSetMouseButtonCallback(m_window, on_mouse_pressed);
  glfwSetKeyCallback(m_window, on_key_pressed);
}

Application::~Application()
{
  std::cout << "Application::~Application(): begin" << std::endl;

  delete m_inputHandler;
  delete m_assetsMgr;
  delete m_audioEngine;
  delete m_renderer;

  glfwTerminate();

  std::cout << "Application::~Application(): end" << std::endl;
}

int Application::run(Scene *scene)
{
  double currentTime = 0;
  double prevTime = 0;
  double timeDelta = 0;

  int exitCode;

  std::cout << "Application::run(): main loop" << std::endl;

  while (!glfwWindowShouldClose(m_window))
  {
    currentTime = glfwGetTime();
    timeDelta = currentTime - prevTime;

    m_inputHandler->dispatch(m_window);
    scene->update(timeDelta);
    if (scene->m_state == SCENE_STATE_EXIT)
      return scene->m_exitCode;

    m_renderer->clearBuffers();
    scene->render();
    m_renderer->flush();
    glfwSwapBuffers(m_window);

    glfwPollEvents();
#ifdef __APPLE__
    fix_render_on_mac(m_window);
#endif
    prevTime = currentTime;
  }

  std::cout << "Application::run(): end" << std::endl;
}

void Application::onResize(GLFWwindow *window, int width, int height)
{
  // NOTE: useless for our needs
}

void Application::onMouseMove(GLFWwindow *window, double x, double y)
{
  // NOTE: useless for our needs
}

void Application::onMousePressed(GLFWwindow *window, int button, int action, int mods)
{
  // NOTE: useless for our needs
}

void Application::onKeyPressed(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  // NOTE: useless for our needs
}

void fix_render_on_mac(GLFWwindow *window)
{
#ifdef __APPLE__
  static bool macMoved = false;
  if (!macMoved)
  {
    int x, y;
    glfwGetWindowPos(window, &x, &y);
    glfwSetWindowPos(window, ++x, y);
    macMoved = true;
  }
#endif
}

void error_callback(int error, const char *description)
{
  std::cerr << "error_callback" << description << std::endl;
}

void on_resize(GLFWwindow *window, int width, int height)
{
  Application *application = (Application *)glfwGetWindowUserPointer(window);
  application->onResize(window, width, height);
}

void on_mouse_move(GLFWwindow *window, double x, double y)
{
  Application *application = (Application *)glfwGetWindowUserPointer(window);
  application->onMouseMove(window, x, y);
}

void on_mouse_pressed(GLFWwindow *window, int button, int action, int mods)
{
  Application *application = (Application *)glfwGetWindowUserPointer(window);
  application->onMousePressed(window, button, action, mods);
}

void on_key_pressed(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  Application *application = (Application *)glfwGetWindowUserPointer(window);
  application->onKeyPressed(window, key, scancode, action, mods);
}
