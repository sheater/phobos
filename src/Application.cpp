#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>

#include "Application.h"
#include "ColladaLoader.h"
#include "TextureLoader.h"
#include "ModelNode.h"
#include "SceneGroup.h"

class Spaceship: public ModelNode
{
public:
  Spaceship(float shift)
    : ModelNode("assets/models/spaceship/model.dae"), m_spin(0.0f), m_shift(shift)
  {
    m_speed = (rand() % 1000) * 0.2;
  }

  void update(float timeDelta)
  {
    glm::mat4 transform(1.0f);

    transform = glm::translate(transform, glm::vec3(m_shift * 2.5f, -0.5f, -12.0));

    transform = glm::rotate(
      transform,
      glm::radians(m_spin * m_speed),
      glm::vec3(0.7f, 1.0f, 0.5f));

    m_transformMatrix = glm::rotate(
      transform,
      glm::radians(-90.0f),
      glm::vec3(1.0f, 0.0f, 0.0f));

    m_spin += timeDelta;
  }

private:
  float m_shift;
  float m_spin;
  float m_speed;
};

class Squad: public SceneGroup
{
public:
  Squad(float lift) : m_lift(lift) {}

  void initialise()
  {
    m_transformMatrix = glm::translate(m_transformMatrix, glm::vec3(0.0f, m_lift, 0.0));

    for (int i = 0; i < 5; i++)
    {
      Spaceship* spaceship = new Spaceship(-2.0f + i);

      attachNode(spaceship);
    }
  }

private:
  float m_lift;
};

Application::Application(unsigned int width, unsigned int height)
    : m_width(width), m_height(height)
{
  m_renderer = new Renderer();
  m_renderer->setViewport(width, height);

  m_assetsMgr = new AssetsManager(m_renderer);
  m_assetsMgr->addLoader(new ColladaLoader());
  m_assetsMgr->addLoader(new TextureLoader());

  m_scene = new Scene(m_renderer, m_assetsMgr);

  // Spaceship* spaceship = new Spaceship();
  m_scene->attachNode(new Squad(3.0f));
  m_scene->attachNode(new Squad(0.0f));
  m_scene->attachNode(new Squad(-3.0f));
}

Application::~Application()
{
  delete m_scene;
  delete m_assetsMgr;
  delete m_renderer;
}

void Application::frame(float timeDelta)
{
  m_scene->update(timeDelta);

  m_renderer->clearBuffers();
  m_scene->render();
  m_renderer->flush();
}

void Application::onResize(GLFWwindow *window, int width, int height)
{
}

void Application::onMouseMove(GLFWwindow *window, double x, double y)
{
}

void Application::onMousePressed(GLFWwindow *window, int button, int action, int mods)
{
}

void Application::onKeyPressed(GLFWwindow *window, int key, int scancode, int action, int mods)
{
}
