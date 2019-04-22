#include "../engine/Scene.h"
#include "Projectile.h"
#include "Player.h"

Projectile::Projectile(Scene *scene, glm::vec3 position, float direction, Spaceship *shooter)
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

Projectile::~Projectile()
{
  ParticleSystem *particleSystem = getScene()->getParticleSystem();
  particleSystem->releaseParticle(m_particle);
}

void Projectile::update(float timeDelta)
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

void Projectile::onCollision(SceneNode *collider)
{
  // we can't shot ourself
  if (collider == m_shooter)
    return;

  if (Spaceship *ship = dynamic_cast<Spaceship *>(collider))
  {
    getScene()->releaseNode(this);
    getScene()->releaseNode(collider);

    if (Player *player = dynamic_cast<Player *>(m_shooter))
    {
      player->addScore(100);
    }
  }
}
