#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "SceneNode.h"
#include "Scene.h"

SceneNode::SceneNode(Scene *scene)
    : m_scene(scene),
      m_parent(nullptr),
      m_collisionHull(nullptr),
      localTransform(glm::mat4(1.0f))
{
}

SceneNode::~SceneNode()
{
  // std::cout << "SceneNode::~SceneNode(): begin" << std::endl;
  for (std::vector<SceneNode *>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
  {
    delete *it;
  }
  // std::cout << "SceneNode::~SceneNode(): end" << std::endl;
}

void SceneNode::attachNode(SceneNode *node)
{
  node->m_parent = this;
  m_nodes.push_back(node);
}

void SceneNode::releaseNode(SceneNode *node)
{
  std::vector<SceneNode *>::iterator it = std::find(m_nodes.begin(), m_nodes.end(), node);
  if (it != m_nodes.end())
  {
    delete node;
    m_nodes.erase(it);
  }
}

void SceneNode::move(const glm::vec3 &vec)
{
  localTransform = glm::translate(localTransform, vec);
}

void SceneNode::rotate(float angle, const glm::vec3 &vec)
{
  localTransform = glm::rotate(localTransform, glm::radians(angle), vec);
}

void SceneNode::render()
{
  Scene *scene = getScene();

  if (m_collisionHull && scene->renderCollisionHulls)
    m_collisionHull->render(scene->getRenderer());

  for (std::vector<SceneNode *>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
    (*it)->render();
}

void SceneNode::update(float timeDelta)
{
  // NOTE: cannot use iterators due to iterators invalidation when array is reallocated
  for (int i = 0; i < m_nodes.size(); i++)
    m_nodes[i]->update(timeDelta);
}

void SceneNode::grabCollisionHulls(std::vector<CollisionHull *> &hulls)
{
  if (m_collisionHull)
    hulls.push_back(m_collisionHull);

  grabChildrenCollisionHulls(hulls);
}

void SceneNode::grabChildrenCollisionHulls(std::vector<CollisionHull *> &hulls)
{
  for (std::vector<SceneNode *>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
    (*it)->grabCollisionHulls(hulls);
}

glm::mat4 SceneNode::getAbsoluteTransform()
{
  if (!m_parent)
    return localTransform;

  return m_parent->getAbsoluteTransform() * localTransform;
}
