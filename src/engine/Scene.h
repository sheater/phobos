#pragma once

#include <vector>

#include "Renderer.h"
#include "AssetsManager.h"
#include "InputHandler.h"
#include "ParticleSystem.h"
#include "SceneNode.h"
#include "UIManager.h"
#include "UILabel.h"

#define SCENE_NO_EXIT -1

enum SceneState
{
  SCENE_STATE_RUNNING = 0,
  SCENE_STATE_EXIT
};

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
  void exitScene(int code);

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
  friend class Application;

  Renderer *m_renderer;
  AssetsManager *m_assetsMgr;
  InputHandler *m_inputHandler;
  ParticleSystem *m_particleSystem;
  UIManager *m_uiMgr;

  UILabel* m_fpsLabel;
  float m_fpsUpdateCounter;
  SceneState m_state;
  int m_exitCode;
};
