#pragma once

#include <string>

#include "SceneNode.h"
#include "Model.h"

class ModelNode: public SceneNode {
public:
  ModelNode(const std::string& path);

  void initialise();
  void render(const glm::mat4& transform);

private:
  std::string m_path;
  Model* m_model;
};
