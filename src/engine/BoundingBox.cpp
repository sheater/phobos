#include <glm/gtc/matrix_transform.hpp>
#include <stdexcept>
#include <algorithm>

#include "BoundingBox.h"
#include "Geometry.h"
#include "VertexBuffer.h"

BoundingBox::BoundingBox(const glm::vec3 &min, const glm::vec3 &max)
    : m_absoluteMin(min),
      m_absoluteMax(max),
      m_relativeMin(min),
      m_relativeMax(max)
{
}

void BoundingBox::render(Renderer *renderer)
{
  glm::vec3 size = m_absoluteMax - m_absoluteMin;
  Geometry *geometry = Geometry::createBox(size);
  VertexBuffer *vertexBuffer = renderer->createVertexBuffer(geometry);

  glm::mat4 transform = glm::translate(
      glm::mat4(1.0f),
      glm::vec3(m_absoluteMin + size * 0.5f));
  Material *material = new Material();
  material->polygonMode = POLYGON_MODE_LINES;

  vertexBuffer->render(transform, material);
  renderer->removeVertexBuffer(vertexBuffer);

  delete geometry;
  delete material;
}

bool BoundingBox::isCollision(CollisionHull *hull)
{
  if (BoundingBox *box = dynamic_cast<BoundingBox *>(hull))
  {
    const glm::vec3 &ourMin = m_absoluteMin;
    const glm::vec3 &ourMax = m_absoluteMax;
    const glm::vec3 &theirMin = box->m_absoluteMin;
    const glm::vec3 &theirMax = box->m_absoluteMax;

    bool noIntersection = (theirMax.x < ourMin.x || theirMin.x > ourMax.x ||
                           theirMax.y < ourMin.y || theirMin.y > ourMax.y ||
                           theirMax.z < ourMin.z || theirMin.z > ourMax.z);

    return !noIntersection;
  }
  else
    throw std::runtime_error("Not implemented");
}

void BoundingBox::expandByPoint(const glm::vec3 &position)
{
  for (int i = 0; i < 3; i++)
  {
    m_absoluteMax[i] = m_relativeMax[i] = std::max(m_relativeMax[i], position[i]);
    m_absoluteMin[i] = m_relativeMin[i] = std::min(m_relativeMin[i], position[i]);
  }
}

void BoundingBox::expandByCollisionHull(CollisionHull *hull)
{
  if (BoundingBox *box = dynamic_cast<BoundingBox *>(hull))
  {
    expandByPoint(box->m_absoluteMin);
    expandByPoint(box->m_absoluteMax);
  }
}

void BoundingBox::expandByGeometry(Geometry *geometry)
{
  for (
      std::vector<glm::vec3>::iterator it = geometry->positions.begin();
      it != geometry->positions.end();
      it++)
  {
    expandByPoint(*it);
  }
}

void BoundingBox::transform(const glm::mat4 &matrix)
{
  m_absoluteMax = glm::vec3(matrix * glm::vec4(m_relativeMax, 1.0f));
  m_absoluteMin = glm::vec3(matrix * glm::vec4(m_relativeMin, 1.0f));
}

void BoundingBox::reset()
{
  m_absoluteMax = m_relativeMax = glm::vec3(-INFINITY);
  m_absoluteMin = m_relativeMin = glm::vec3(INFINITY);
}
