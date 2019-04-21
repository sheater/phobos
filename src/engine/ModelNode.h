#pragma once

#include <string>

#include "SceneNode.h"
#include "Model.h"

class ModelNode : public SceneNode
{
public:
  ModelNode(
    Scene* scene,
    const std::string &path,
    const glm::mat4& preprocessTransformMatrix = glm::mat4(1.0f));
  ~ModelNode();

  void update(float timeDelta);
};
