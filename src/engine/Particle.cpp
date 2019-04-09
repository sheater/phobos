#include "ParticleSystem.h"

Particle::Particle(ParticleSystem *particleSystem)
    : m_particleSystem(particleSystem),
      position(0.0f),
      size(1.0f),
      color(1.0f),
      life(INFINITY),
      velocity(0.0f),
      acceleration(0.0f),
      texture(nullptr)
{
}

void Particle::update(float timeDelta)
{
  if (life == INFINITY)
    return;

  life -= timeDelta * 0.1f;

  position += velocity * timeDelta;

  if (life <= 0.0f)
    m_particleSystem->releaseParticle(this);
}
