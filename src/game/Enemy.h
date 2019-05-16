#pragma once

#include "Spaceship.h"

#define ENEMY_MOVEMENT_SPEED 1.0f

class Enemy : public Spaceship
{
public:
  Enemy(Scene *scene, const glm::vec2 &initialPosition)
      : Spaceship(scene, "assets/models/spaceship2/model.dae", getPreprocessTransform())
  {
    m_state = SPACESHIP_STATE_IDLE;
    m_position.x = initialPosition.x;
    m_position.y = initialPosition.y;
    m_direction = 180.0f;
  }

  void update(float timeDelta)
  {
    m_position.y -= ENEMY_MOVEMENT_SPEED * timeDelta;

    if (m_state == SPACESHIP_STATE_IDLE)
    {
      if (m_position.y > 3.0f)
        return;
      else
        m_state = SPACESHIP_STATE_ACTIVE;
    }

    if (m_position.y < -3.0f)
    {
      getScene()->releaseNode(this);
      return;
    }

    Spaceship::update(timeDelta);
  }

  void render()
  {
    if (m_state == SPACESHIP_STATE_IDLE)
      return;

    Spaceship::render();
  }

  static glm::mat4 getPreprocessTransform()
  {
    glm::mat4 transform = glm::rotate(
        glm::mat4(1.0f), glm::radians(90.0f),
        glm::vec3(0.0f, 0.0f, 1.0f));

    return glm::scale(transform, glm::vec3(0.0012f));
  }
};
