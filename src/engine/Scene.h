#pragma once

#include <vector>

#include "Renderer.h"
#include "AssetsManager.h"
#include "InputHandler.h"
#include "ParticleSystem.h"
#include "SceneNode.h"

class Scene : public SceneNode
{
public:
  Scene(
      Renderer *renderer,
      AssetsManager *assetsMgr,
      InputHandler *inputHandler);

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

private:
  Renderer *m_renderer;
  AssetsManager *m_assetsMgr;
  InputHandler *m_inputHandler;
  ParticleSystem *m_particleSystem;
};
