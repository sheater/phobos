#pragma once

#include <glm/glm.hpp>

class Light
{
public:
  Light()
      : color(glm::vec4(1.0f)),
        position(glm::vec3(0.0f))
  {
  }

  glm::vec4 color;
  glm::vec3 position;
};
