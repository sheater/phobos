#pragma once

#include <string>

#include "../engine/ModelNode.h"

class Spaceship : public ModelNode
{
public:
  Spaceship(
      Scene *scene,
      const std::string &path,
      const glm::mat4 &preprocessTransformMatrix)
      : ModelNode(scene, path, preprocessTransformMatrix)
  {
  }
};
