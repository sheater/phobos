#pragma once

#include <glm/glm.hpp>

#include "CollisionHull.h"
#include "Renderer.h"

class BoundingBox : public CollisionHull
{
public:
  BoundingBox();

  void render(Renderer *renderer);
  bool isColliding(CollisionHull *hull);

  void maybeExpand(const glm::vec3 &position);
  void transform(const glm::mat4 &matrix);

// private:
  glm::vec3 m_relativeMin;
  glm::vec3 m_relativeMax;

  glm::vec3 m_absoluteMin;
  glm::vec3 m_absoluteMax;
};
