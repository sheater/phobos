#include "SceneGroup.h"

SceneGroup::SceneGroup()
  : SceneNode()
{
}

SceneGroup::~SceneGroup()
{
  for (std::vector<SceneNode *>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
  {
    delete *it;
  }
}

void SceneGroup::attachNode(SceneNode* node)
{
  node->m_renderer = m_renderer;
  node->m_assetsMgr = m_assetsMgr;
  node->m_scene = m_scene;
  node->m_parent = this;
  node->initialise();

  m_nodes.push_back(node);

  std::cout << "Node attached" << std::endl;
}

void SceneGroup::render(const glm::mat4& transform)
{
  glm::mat4 finalTransform = transform * m_transformMatrix;
  for (std::vector<SceneNode *>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
  {
    (*it)->render(finalTransform);
  }
}

void SceneGroup::update(float timeDelta)
{
  for (std::vector<SceneNode *>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
  {
    (*it)->update(timeDelta);
  }
}
