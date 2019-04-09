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

  void render(const glm::mat4 &transformMatrix)
  {
    const glm::mat4 finalModelMatrix = transformMatrix * transform;
    vertexBuffer->render(finalModelMatrix, material);
  }

  BoundingBox *createBoundingBox()
  {
    BoundingBox *bbox = new BoundingBox();

    for (
        std::vector<glm::vec3>::iterator it = geometry->positions.begin();
        it != geometry->positions.end();
        it++)
    {
      bbox->maybeExpand(*it);
    }

    return bbox;
  }

  Geometry *geometry; // for collisions
  VertexBuffer *vertexBuffer;
  Material *material;
  glm::mat4 transform;
};
