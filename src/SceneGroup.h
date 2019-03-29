#pragma once

#include "SceneNode.h"

class SceneGroup: public SceneNode {
public:
  SceneGroup();
  ~SceneGroup();

  void attachNode(SceneNode* node);
  void render(const glm::mat4& transform = glm::mat4(1.0f));
  void update(float timeDelta);

protected:
  friend class SceneNode;

  std::vector<SceneNode *> m_nodes;
};
