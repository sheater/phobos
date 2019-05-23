#pragma once

#include <glm/glm.hpp>

class Light
{
public:
  Light()
      : ambientColor(glm::vec4(0.0f)),
        diffuseColor(glm::vec4(1.0f)),
        specularColor(glm::vec4(0.5f)),
        position(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f))
  {
  }

  void setPosition(const glm::vec3& pos) {
    position.x = pos.x;
    position.y = pos.y;
    position.z = pos.z;
  }

  void makePointLight() {
    position.w = 1.0f;
  }

  void makeDirectionalLight() {
    position.w = 0.0f;
  }

  glm::vec4 ambientColor;
  glm::vec4 diffuseColor;
  glm::vec4 specularColor;
  glm::vec4 position;
};
