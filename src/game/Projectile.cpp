#include "../engine/Scene.h"
#include "Projectile.h"
#include "Player.h"

Projectile::Projectile(Scene *scene, glm::vec3 position, float direction, Spaceship *shooter)
    : SceneNode(scene),
      m_position(position),
      m_direction(direction),
      m_shooter(shooter)
{
  AssetsManager *assetsMgr = scene->getAssetsManager();
  m_fireballTexture = static_cast<Texture *>(assetsMgr->getAsset("assets/textures/fireball.png"));

  ParticleSystem *particleSystem = scene->getParticleSystem();
  m_particle = particleSystem->emitParticle();
  m_particle->position = m_position;
  m_particle->texture = m_fireballTexture;
  m_particle->size = glm::vec2(0.03f, 0.03f);

  m_collisionHull = new BoundingBox(glm::vec3(-0.05), glm::vec3(0.05));

  m_light = new Light();
  m_light->ambientColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
  m_light->diffuseColor = glm::vec4(0.4f, 0.3f, 0.1f, 1.0f);
  m_light->specularColor = glm::vec4(0.5f, 0.4f, 0.2f, 1.0f);
  scene->getRenderer()->addLight(m_light);
}

Projectile::~Projectile()
{
  Scene* scene = getScene();

  ParticleSystem *particleSystem = scene->getParticleSystem();
  particleSystem->releaseParticle(m_particle);

  scene->getRenderer()->removeLight(m_light);
}

void Projectile::update(float timeDelta)
{
  SceneNode::update(timeDelta);
  glm::vec3 &position = m_particle->position;

  float shift = timeDelta * PROJECTILE_SPEED;
  position.x += cos(glm::radians(m_direction)) * shift;
  position.y += sin(glm::radians(m_direction)) * shift;

  m_light->setPosition(position);

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
    ship->explode();

    if (Player *player = dynamic_cast<Player *>(m_shooter))
    {
      player->addScore(100);
    }
  }
}
