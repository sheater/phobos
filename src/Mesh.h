#pragma once

#include <glm/glm.hpp>

#include "VertexBuffer.h"
#include "Material.h"

class Mesh
{
public:
  Mesh() : vertexBuffer(nullptr), material(nullptr), transform(glm::mat4(1.0f)) {}

  void render(const glm::mat4 &model)
  {
    const glm::mat4 finalTransform = model * transform;
    vertexBuffer->render(finalTransform, material);
  }

  VertexBuffer *vertexBuffer;
  Material *material;
  glm::mat4 transform;
};
