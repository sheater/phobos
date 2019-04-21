#pragma once

#include <glm/glm.hpp>

#include "VertexBuffer.h"
#include "Material.h"
#include "BoundingBox.h"

class Mesh
{
public:
  Mesh()
      : vertexBuffer(nullptr),
        material(nullptr),
        geometry(nullptr),
        transform(glm::mat4(1.0f))
  {
  }

  ~Mesh()
  {
    if (geometry)
    {
      delete geometry;
    }
  }

  Geometry *geometry; // for collisions
  VertexBuffer *vertexBuffer;
  Material *material;
  glm::mat4 transform;
};
