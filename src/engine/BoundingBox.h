#pragma once

#include <glm/glm.hpp>

#include "CollisionHull.h"
#include "Renderer.h"

class BoundingBox : public CollisionHull
{
public:
  BoundingBox(const glm::vec3 &min = glm::vec3(-1.0f), const glm::vec3 &max = glm::vec3(1.0f));

  void render(Renderer *renderer);
  bool isCollision(CollisionHull *hull);

  void expandByGeometry(Geometry *geometry);
  void expandByCollisionHull(CollisionHull *hull);
  void expandByPoint(const glm::vec3 &position);
  void transform(const glm::mat4 &matrix);
  void reset();

  // private:
  glm::vec3 m_relativeMin;
  glm::vec3 m_relativeMax;

  glm::vec3 m_absoluteMin;
  glm::vec3 m_absoluteMax;
};
