#include "ParticleSystem.h"

Particle::Particle(ParticleSystem *particleSystem)
    : m_particleSystem(particleSystem),
      position(0.0f),
      size(1.0f),
      color(1.0f),
      life(INFINITY),
      agingRate(0.1f),
      velocity(0.0f),
      acceleration(0.0f),
      texture(nullptr)
{
}

void Particle::update(float timeDelta)
{
  if (life == INFINITY)
    return;

  // TODO: take acceleration in count
  life -= timeDelta * agingRate;
  position += velocity * timeDelta;

  if (life <= 0.0f)
    m_particleSystem->releaseParticle(this);
}
