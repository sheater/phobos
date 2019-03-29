#include <iostream>

#include "Scene.h"

Scene::Scene(Renderer* renderer, AssetsManager* assetsMgr)
  : SceneGroup()
{
  m_renderer = renderer;
  m_assetsMgr = assetsMgr;
  m_scene = this;
}
