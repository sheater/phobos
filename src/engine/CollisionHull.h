#pragma once

#include "Renderer.h"

class CollisionHull
{
public:
  virtual void render(Renderer *renderer) {}
  virtual bool isCollision(CollisionHull *hull) {}
  virtual void transform(const glm::mat4 &matrix) {}
};
