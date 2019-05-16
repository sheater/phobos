#pragma once

#include <iostream>

#include "../engine/ParticleSystem.h"
#include "../engine/SceneNode.h"
#include "../engine/Light.h"
#include "Spaceship.h"

#define PROJECTILE_SPEED 4.0f

#define PROJECTILE_X_THRESHOLD 3.0f
#define PROJECTILE_Y_THRESHOLD 3.0f

class Projectile : public SceneNode
{
private:
  Texture *m_fireballTexture;
  Spaceship *m_shooter;
  Particle *m_particle;
  Light *m_light;
  glm::vec3 m_position;
  float m_direction;

public:
  Projectile(Scene *scene, glm::vec3 position, float direction, Spaceship *shooter);
  ~Projectile();

  void update(float timeDelta);
  void onCollision(SceneNode *collider);
};
