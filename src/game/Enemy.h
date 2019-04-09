#pragma once

#include "Spaceship.h"

class Enemy : public Spaceship
{
public:
  Enemy(Scene *scene) : Spaceship(scene, "", getPreprocessTransform())
  {
    // kokot
  }

  static glm::mat4 getPreprocessTransform()
  {
    glm::mat4 transform = glm::rotate(
        glm::mat4(1.0f), glm::radians(90.0f),
        glm::vec3(0.0f, 0.0f, 1.0f));

    return glm::scale(transform, glm::vec3(0.0012f));
  }
};
