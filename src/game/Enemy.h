#pragma once

#include "../engine/utils.h"
#include "Spaceship.h"

#define ENEMY_MOVEMENT_SPEED 1.0f

class Enemy : public Spaceship
{
public:
  Enemy(Scene *scene)
      : Spaceship(scene, "assets/models/spaceship2/model.dae", getPreprocessTransform())
  {
    m_position.y = 3.0f;
    m_position.x = randomFloatInterval(-3.0f, 3.0f);
    m_direction = 180.0f;
  }

  void update(float timeDelta)
  {
    m_position.y -= ENEMY_MOVEMENT_SPEED * timeDelta;

    if (m_position.y < -3.0f)
    {
      getScene()->releaseNode(this);
      return;
    }

    Spaceship::update(timeDelta);
  }

  static glm::mat4 getPreprocessTransform()
  {
    glm::mat4 transform = glm::rotate(
        glm::mat4(1.0f), glm::radians(90.0f),
        glm::vec3(0.0f, 0.0f, 1.0f));

    return glm::scale(transform, glm::vec3(0.0012f));
  }
};
