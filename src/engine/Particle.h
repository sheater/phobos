#pragma once

#include <vector>

#include "Texture.h"

class ParticleSystem;

class Particle
{
public:
  Particle(ParticleSystem *particleSystem);
  void update(float timeDelta);

  glm::vec3 position;
  glm::vec3 velocity;
  glm::vec3 acceleration;
  glm::vec4 color;
  glm::vec2 size;
  float life;

  Texture *texture;

private:
  ParticleSystem *m_particleSystem;
};
