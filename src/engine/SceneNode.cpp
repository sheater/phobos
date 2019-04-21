#include <glm/gtc/matrix_transform.hpp>

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
  for (std::vector<SceneNode *>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
  {
    delete *it;
  }
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
    delete *it;
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
  int i, j;
  // NOTE: cannot use iterators due to iterators invalidation when array is reallocated
  for (i = 0; i < m_nodes.size(); i++)
  {
    m_nodes[i]->update(timeDelta);

  //   // m_nodes[i]->checkCollision();

  //   for (j = 0; j < m_nodes.size(); j++)
  //   {
  //     if (i == j)
  //       continue;

  //     checkCollision(m_nodes[j]);
  //     // isCollision(m_nodes[j])
  //   }
  }
}

// void SceneNode::checkCollision(SceneNode *other)
// {
//   if (m_collisionHull->isCollision(other->m_collisionHull))
//     onCollision(other);

//   for (
//       std::vector<SceneNode *>::iterator it = m_nodes.begin();
//       it != m_nodes.end();
//       it++)
//     it->checkCollision(other);
// }

glm::mat4 SceneNode::getAbsoluteTransform()
{
  if (!m_parent)
    return localTransform;

  return m_parent->getAbsoluteTransform() * localTransform;
}
