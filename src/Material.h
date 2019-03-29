#pragma once

#include <glm/glm.hpp>

#include "Texture.h"

class Material
{
public:
  Material()
      : diffuseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)), texture(nullptr) {}

  glm::vec4 diffuseColor;
  Texture *texture;
};
