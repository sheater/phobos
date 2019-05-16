#pragma once

#include "../engine/ModelNode.h"

class Introship : public ModelNode
{
public:
  Introship(Scene *scene)
      : ModelNode(scene, "assets/models/spaceship3/model.dae", getPreprocessTransform())
  {
    m_movement = 0.0f;
  }

  glm::mat4 getPreprocessTransform()
  {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.08f, 0.0f, 0.0f));

    transform = glm::rotate(
        transform, glm::radians(180.0f),
        glm::vec3(0.0f, 0.0f, 1.0f));

    return glm::scale(transform, glm::vec3(0.001f)); // spaceship3
  }

  void update(float timeDelta)
  {
    m_movement += timeDelta * 1.5f;

    localTransform = glm::translate(
        glm::mat4(1.0f),
        glm::vec3(sin(m_movement) * 0.3, 0.15f, -2.0f + sin(m_movement * 2.0f) * 0.1));

    localTransform = glm::rotate(
        localTransform,
        glm::radians(20.0f * sin(m_movement)),
        glm::vec3(0.0f, 1.0f, 0.0f));
  }

private:
  float m_movement;
};
