#pragma once

#include <vector>

#include "Renderer.h"
#include "AssetsManager.h"
#include "InputHandler.h"
#include "ParticleSystem.h"
#include "SceneNode.h"
#include "UIManager.h"
#include "UILabel.h"

class Scene : public SceneNode
{
public:
  Scene(
      Renderer *renderer,
      AssetsManager *assetsMgr,
      InputHandler *inputHandler);
  ~Scene();

  void render();
  void update(float timeDelta);

  inline Renderer *getRenderer()
  {
    return m_renderer;
  }

  inline AssetsManager *getAssetsManager()
  {
    return m_assetsMgr;
  }

  inline InputHandler *getInputHandler()
  {
    return m_inputHandler;
  }

  inline ParticleSystem *getParticleSystem()
  {
    return m_particleSystem;
  }

  inline UIManager *getUIManager()
  {
    return m_uiMgr;
  }

  bool renderCollisionHulls = false;

protected:
  void checkCollisions();

private:
  Renderer *m_renderer;
  AssetsManager *m_assetsMgr;
  InputHandler *m_inputHandler;
  ParticleSystem *m_particleSystem;
  UIManager *m_uiMgr;

  UILabel* m_fpsLabel;
  float m_fpsUpdateCounter;
};
