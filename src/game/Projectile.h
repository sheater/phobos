#pragma once

#include "../engine/ParticleSystem.h"
#include "../engine/SceneNode.h"
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
  glm::vec3 m_position;
  float m_direction;

public:
  Projectile(Scene *scene, glm::vec3 position, float direction, Spaceship *shooter)
      : SceneNode(scene),
        m_position(position),
        m_direction(direction),
        m_shooter(shooter)
  {
    AssetsManager *assetsMgr = getScene()->getAssetsManager();
    m_fireballTexture = static_cast<Texture *>(assetsMgr->getAsset("assets/textures/fireball.png"));

    ParticleSystem *particleSystem = getScene()->getParticleSystem();
    m_particle = particleSystem->emitParticle();
    m_particle->position = m_position;
    m_particle->texture = m_fireballTexture;
    m_particle->size = glm::vec2(0.03f, 0.03f);

    m_collisionHull = new BoundingBox(glm::vec3(-0.05), glm::vec3(0.05));
  }

  ~Projectile()
  {
    ParticleSystem *particleSystem = getScene()->getParticleSystem();
    particleSystem->releaseParticle(m_particle);
  }

  void update(float timeDelta)
  {
    SceneNode::update(timeDelta);
    glm::vec3 &position = m_particle->position;

    float shift = timeDelta * PROJECTILE_SPEED;
    position.x += cos(glm::radians(m_direction)) * shift;
    position.y += sin(glm::radians(m_direction)) * shift;

    m_collisionHull->transform(glm::translate(glm::mat4(1.0f), position));

    if (
        position.x > PROJECTILE_X_THRESHOLD ||
        position.x < -PROJECTILE_X_THRESHOLD ||
        position.y > PROJECTILE_Y_THRESHOLD ||
        position.y < -PROJECTILE_Y_THRESHOLD)
    {
      getScene()->releaseNode(this);
    }
  }
};
