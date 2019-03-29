#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "ModelNode.h"

ModelNode::ModelNode(const std::string& path)
  : SceneNode(), m_path(path)
{
}

void ModelNode::initialise()
{
  m_model = static_cast<Model *>(m_assetsMgr->getAsset(m_path));
}

void ModelNode::render(const glm::mat4& transform)
{
  if (!m_model)
    return;

  glm::mat4 finalTransform = transform * m_transformMatrix;
  m_model->render(finalTransform);
}
