#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <glm/gtc/matrix_transform.hpp>

#include "Application.h"
#include "Mesh.h"
#include "Texture.h"
#include "GpuProgram.h"
#include "Model.h"
#include "Renderer.h"

void on_resize(GLFWwindow *window, int width, int height);
void on_mouse_move(GLFWwindow *window, double x, double y);
void on_mouse_pressed(GLFWwindow *window, int button, int action, int mods);
void on_key_pressed(GLFWwindow *window, int key, int scancode, int action, int mods);

// Texture *texture;
// GpuProgram *program;
// Model *model;
// RenderObject *renderObject;
// Renderer *renderer;

// Application::Application(unsigned int initial_width, unsigned int initial_height)
// {
//   width = initial_width;
//   height = initial_height;

//   renderer = new Renderer();

//   renderer->setViewport(width, height);

//   Mesh *mesh = Mesh::createBox(1, 1, 1);
//   renderObject = mesh->createRenderObject(renderer);
//   delete mesh;
//   // model = Model::createFromFile("assets/models/weapon/model.dae", renderer);

  
// }

// Application::~Application()
// {
//   delete renderObject;
//   delete texture;
//   delete program;
//   // delete model;
//   delete renderer;
// }

// void Application::render()
// {
//   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//   // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

//   glm::mat4 transform(1.0f);

//   transform = glm::translate(transform, glm::vec3(0.0f, -0.5f, -3.0));

//   transform = glm::rotate(
//       transform,
//       glm::radians((GLfloat)glfwGetTime() * 50.0f),
//       glm::vec3(0.0f, 1.0f, 0.0f));
//   transform = glm::rotate(transform, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

//   model->render(transform);
//   // renderObject->render(transform);
// }

// void Application::on_resize(GLFWwindow *window, int width, int height)
// {
//   this->width = width;
//   this->height = height;

//   glViewport(0, 0, width, height);
// }

// void Application::on_mouse_move(GLFWwindow *window, double x, double y) {}
// void Application::on_mouse_pressed(GLFWwindow *window, int button, int action, int mods) {}
// void Application::on_key_pressed(GLFWwindow *window, int key, int scancode, int action, int mods) {}

void error_callback(int error, const char *description)
{
  std::cerr << "error_callback" << description << std::endl;
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

void run()
{
  const size_t initial_width = 1024;
  const size_t initial_height = 768;

  // Initialize GLFW
  if (!glfwInit())
  {
    throw std::runtime_error("Could not initialize GLFW!");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  // glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
  glfwSetErrorCallback(error_callback);

  GLFWwindow *window = glfwCreateWindow(initial_width, initial_height, "Phobos", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    throw std::runtime_error("Could not create a window!");
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  const char *openGLVersion = reinterpret_cast<const char *>(glGetString(GL_VERSION));
  std::cout << "OpenGL version: " << openGLVersion << std::endl;

  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    glfwTerminate();
    throw std::runtime_error("Could not create a glew!");
  }

  {
    Application application(initial_width, initial_height);

    glfwSetWindowUserPointer(window, &application);
    glfwSetWindowSizeCallback(window, on_resize);
    glfwSetCursorPosCallback(window, on_mouse_move);
    glfwSetMouseButtonCallback(window, on_mouse_pressed);
    glfwSetKeyCallback(window, on_key_pressed);

    double currentTime = 0;
    double prevTime = 0;
    double delta = 0;
    GLenum error = GL_NO_ERROR;
    while (!glfwWindowShouldClose(window))
    {
      currentTime = glfwGetTime();
      delta = currentTime - prevTime;

      application.frame(delta);

      glfwSwapBuffers(window);

      glfwPollEvents();
      fix_render_on_mac(window);
      prevTime = currentTime;
    }

    // Free the entire application before terminating glfw. If this were done in the wrong order
    // application may crash on calling OpenGL (Delete*) calls after destruction of a context.
    // Freeing is done implicitly by enclosing this part of code in block {}.
  }

  // Free every allocated resource associated with GLFW
  glfwTerminate();
}

int main(void)
{
  try
  {
    run();
  }
  catch (std::exception &ex)
  {
    std::cerr << ex.what() << std::endl;
    return -1;
  }
  return 0;
}

void on_resize(GLFWwindow *window, int width, int height)
{
  Application *application = (Application *)glfwGetWindowUserPointer(window);
  application->onResize(window, width, height);
  // fix_render_on_mac(window);
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
