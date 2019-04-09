#pragma once

#include "Renderer.h"

class CollisionHull
{
public:
  virtual void render(Renderer *renderer) {}
  virtual bool isColliding(CollisionHull *hull) {}
  virtual void createBoundingBox() {}
};
