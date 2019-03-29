#include <glm/gtc/matrix_transform.hpp>

#include "SceneNode.h"

SceneNode::SceneNode()
: m_parent(nullptr), m_transformMatrix(glm::mat4(1.0f))
{
}

SceneNode::~SceneNode()
{
}

void SceneNode::translate(const glm::vec3& vec)
{
  m_transformMatrix = glm::translate(m_transformMatrix, vec);
}
