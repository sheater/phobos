#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Renderer.h"
#include "AssetsManager.h"

class Scene;
class SceneGroup;

class SceneNode {
public:
  SceneNode();
  ~SceneNode();

  virtual void initialise() {}
  virtual void render(const glm::mat4& transform) {}
  virtual void update(float timeDelta) {}

  void translate(const glm::vec3& vec);

protected:
  friend class SceneGroup;
  friend class Scene;

  glm::mat4 m_transformMatrix;

  Scene* m_scene;
  SceneGroup* m_parent;
  Renderer* m_renderer;
  AssetsManager* m_assetsMgr;
};
