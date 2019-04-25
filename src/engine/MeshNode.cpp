#include "MeshNode.h"
#include "BoundingBox.h"
#include "Scene.h"

MeshNode::MeshNode(Mesh *mesh, Scene *scene)
    : m_originalMesh(mesh), material(nullptr), SceneNode(scene)
{
  if (m_originalMesh->material)
    material = m_originalMesh->material->clone();

  localTransform = m_originalMesh->transform;

  // FIXME: another collision hull types
  m_collisionHull = new BoundingBox();
  m_collisionHull->expandByGeometry(m_originalMesh->geometry);
}

void MeshNode::render()
{
  Renderer* renderer = getScene()->getRenderer();
  material->bind(renderer);
  renderer->setModelViewMatrix(getAbsoluteTransform());
  m_originalMesh->vertexBuffer->render();

  SceneNode::render();
}

void MeshNode::update(float timeDelta)
{
  m_collisionHull->transform(getAbsoluteTransform());

  SceneNode::update(timeDelta);
}
