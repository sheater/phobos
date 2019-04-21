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
}

bool BoundingBox::isCollision(CollisionHull *hull)
{
  if (BoundingBox *box = dynamic_cast<BoundingBox *>(hull))
  {
    const glm::vec3 &min1 = m_absoluteMin;
    const glm::vec3 &max1 = m_absoluteMax;
    const glm::vec3 &min2 = box->m_absoluteMin;
    const glm::vec3 &max2 = box->m_absoluteMax;

    return !(
        (min1.x < max2.x || max1.x > min2.x) &&
        (min1.y < max2.y || max1.y > min2.y) &&
        (min1.z < max2.z || max1.z > min2.z));
  }
  else
  {
    throw std::runtime_error("Not implemented");
  }
}

void BoundingBox::maybeExpand(const glm::vec3 &position)
{
  // m_absoluteMax.x = m_relativeMax.x = std::max(m_relativeMax.x, position.x);
  // m_absoluteMax.y = m_relativeMax.y = std::max(m_relativeMin.y, position.y);
  // m_absoluteMax.z = m_relativeMax.z = std::max(m_relativeMin.z, position.z);

  // m_absoluteMin.x = m_relativeMin.x = std::min(m_relativeMin.x, position.x);
  // m_absoluteMin.y = m_relativeMin.y = std::min(m_relativeMin.y, position.y);
  // m_absoluteMin.z = m_relativeMin.z = std::min(m_relativeMin.z, position.z);
  for (int i = 0; i < 3; i++)
  {
    m_absoluteMax[i] = m_relativeMax[i] = std::max(m_relativeMax[i], position[i]);
    m_absoluteMin[i] = m_relativeMin[i] = std::min(m_relativeMin[i], position[i]);
  }
}

void BoundingBox::transform(const glm::mat4 &matrix)
{
  // const glm::vec3 max = glm::vec3(matrix * glm::vec4(m_relativeMax, 1.0f));
  // const glm::vec3 min = glm::vec3(matrix * glm::vec4(m_relativeMin, 1.0f));

  m_absoluteMax = glm::vec3(matrix * glm::vec4(m_relativeMax, 1.0f));
  m_absoluteMin = glm::vec3(matrix * glm::vec4(m_relativeMin, 1.0f));

  // for (int i = 0; i < 3; i++)
  // {
  //   m_absoluteMax[i] = std::max(m_absoluteMax[i], max[i]);
  //   m_absoluteMin[i] = std::min(m_absoluteMin[i], min[i]);
  // }
}
