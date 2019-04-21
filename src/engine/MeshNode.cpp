#include "MeshNode.h"
#include "BoundingBox.h"

MeshNode::MeshNode(Mesh *mesh, Scene *scene)
    : m_originalMesh(mesh), m_material(nullptr), SceneNode(scene)
{
  if (m_originalMesh->material)
    m_material = m_originalMesh->material->clone();

  localTransform = m_originalMesh->transform;

  // FIXME: another collision hull types
  m_collisionHull = new BoundingBox();
  m_collisionHull->expandByGeometry(m_originalMesh->geometry);
}

void MeshNode::render()
{
  m_originalMesh->vertexBuffer->render(getAbsoluteTransform(), m_material);

  SceneNode::render();
}

void MeshNode::update(float timeDelta)
{
  m_collisionHull->transform(getAbsoluteTransform());

  SceneNode::update(timeDelta);
}
