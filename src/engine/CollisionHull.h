#pragma once

#include "Renderer.h"

class CollisionHull
{
public:
  virtual void render(Renderer *renderer) {}
  virtual bool isCollision(CollisionHull *hull) {}

  virtual void expandByGeometry(Geometry *geometry) {}
  virtual void expandByCollisionHull(CollisionHull *hull) {}
  virtual void expandByPoint(const glm::vec3 &position) {}
  virtual void transform(const glm::mat4 &matrix) {}
  virtual void reset() {}
};
