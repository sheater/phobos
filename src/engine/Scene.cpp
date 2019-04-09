#include <iostream>

#include "Scene.h"

Scene::Scene(
    Renderer *renderer,
    AssetsManager *assetsMgr,
    InputHandler *inputHandler)
    : SceneNode(this),
      m_renderer(renderer),
      m_assetsMgr(assetsMgr),
      m_inputHandler(inputHandler)
{
  m_scene = this;
  m_particleSystem = new ParticleSystem(m_renderer);
}

void Scene::render()
{
  SceneNode::render();
  m_particleSystem->render();
}

void Scene::update(float timeDelta)
{
  SceneNode::update(timeDelta);
  m_particleSystem->update(timeDelta);
}
