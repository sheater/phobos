#pragma once

#include <string>
#include <glm/gtc/matrix_transform.hpp>

#include "../engine/ModelNode.h"

class Spaceship : public ModelNode
{
public:
  Spaceship(
      Scene *scene,
      const std::string &path,
      const glm::mat4 &preprocessTransformMatrix)
      : ModelNode(scene, path, preprocessTransformMatrix)
  {
    m_position = glm::vec3(0.0f, 0.0f, -5.0f);
    m_direction = 0.0f;
    m_tiltAngle = 0.0f;

    // m_collisionHull = new BoundingBox(glm::vec3(-0.3), glm::vec3(0.3));
  }

  void update(float timeDelta)
  {
    localTransform = glm::translate(glm::mat4(1.0f), m_position);
    localTransform = glm::rotate(
        localTransform,
        glm::radians(m_direction),
        glm::vec3(0.0f, 0.0f, 1.0f));
    localTransform = glm::rotate(
        localTransform,
        glm::radians(m_tiltAngle),
        glm::vec3(0.0f, 1.0f, 0.0f));

    ModelNode::update(timeDelta);

    // m_collisionHull->transform(getAbsoluteTransform());
  }

protected:
  float m_tiltAngle;
  float m_direction;
  glm::vec3 m_position;
};
