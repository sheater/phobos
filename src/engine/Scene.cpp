#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Scene.h"

#define FPS_UPDATE_THRESHOLD 0.25f

Scene::Scene(
    Renderer *renderer,
    AssetsManager *assetsMgr,
    InputHandler *inputHandler,
    AudioEngine *audioEngine)
    : m_renderer(renderer),
      m_assetsMgr(assetsMgr),
      m_inputHandler(inputHandler),
      m_audioEngine(audioEngine)
{
  srand(time(NULL));

  // m_scene = this;
  m_uiMgr = new UIManager(m_renderer, m_assetsMgr);
  m_particleSystem = new ParticleSystem(m_renderer);

  m_fpsLabel = new UILabel(m_uiMgr, "", glm::vec2(16.0f, renderer->getHeight() - 24.0f));
  m_uiMgr->attachNode(m_fpsLabel);
  m_state = SCENE_STATE_RUNNING;
  m_exitCode = SCENE_NO_EXIT;

  m_root = new SceneNode(this);
}

Scene::~Scene()
{
  std::cout << "Scene::~Scene(): begin" << std::endl;
  delete m_root;

  delete m_particleSystem;
  delete m_uiMgr;

  std::cout << "Scene::~Scene(): end" << std::endl;
}

void Scene::render()
{
  m_renderer->setProjectionType(PROJECTION_TYPE_PERSPECTIVE);
  m_root->render();
  m_particleSystem->render();

  m_renderer->setProjectionType(PROJECTION_TYPE_ORTHO);
  m_uiMgr->render();
}

void Scene::exitScene(int code)
{
  m_state = SCENE_STATE_EXIT;
  m_exitCode = code;
}

void Scene::update(float timeDelta)
{
  m_root->update(timeDelta);
  m_particleSystem->update(timeDelta);

  checkCollisions();

  m_fpsUpdateCounter += timeDelta;
  if (m_fpsUpdateCounter > FPS_UPDATE_THRESHOLD)
  {
    m_fpsUpdateCounter = 0.0f;
    m_fpsLabel->text = "FPS: " + std::to_string(int(1.0f / timeDelta));
  }
}

void Scene::checkCollisions()
{
  int ai, bi;
  for (ai = 0; ai < m_root->m_nodes.size(); ai++)
  {
    SceneNode *a = m_root->m_nodes[ai];
    CollisionHull *ahull = a->getCollisionHull();

    if (!ahull)
      continue;

    for (bi = 0; bi < m_root->m_nodes.size(); bi++)
    {
      SceneNode *b = m_root->m_nodes[bi];
      // don't check collision with itself
      if (a == b)
        continue;

      CollisionHull *bhull = b->getCollisionHull();

      if (!bhull)
        continue;

      if (ahull->isCollision(bhull))
      {
        // FIXME: more precise collision
        a->onCollision(b);
      }
    }
  }
}
