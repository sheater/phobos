#include "../engine/Scene.h"
#include "Player.h"
#include "actions.h"

Player::Player(Scene *scene)
    : Spaceship(scene, "assets/models/spaceship/model.dae", getPreprocessTransform())
{
  m_sparkTimer = 0.0f;
  m_shootTimer = 0.0f;
  m_heat = 0.0f;
  m_score = 0;

  AssetsManager *assetsMgr = getScene()->getAssetsManager();
  m_sparkTexture = static_cast<Texture *>(assetsMgr->getAsset("assets/textures/spark.png"));
  m_shotSound = static_cast<Sound *>(assetsMgr->getAsset("assets/sounds/missile.wav"));
}

glm::mat4 Player::getPreprocessTransform()
{
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

  transform = glm::rotate(
      transform, glm::radians(180.0f),
      glm::vec3(0.0f, 0.0f, 1.0f));

  return glm::scale(transform, glm::vec3(0.3f));
}

void Player::update(float timeDelta)
{
  bool movingAside = false;
  glm::vec3 moveVec(0.0f);
  InputHandler *input = getScene()->getInputHandler();

  if (input->isActionKeyPressed(PLAYER_ACTION_MOVE_UP))
    moveVec.y = PLAYER_SPEED * timeDelta;

  if (input->isActionKeyPressed(PLAYER_ACTION_MOVE_DOWN))
    moveVec.y = -PLAYER_SPEED * timeDelta;

  if (input->isActionKeyPressed(PLAYER_ACTION_MOVE_LEFT))
  {
    moveVec.x = -PLAYER_SPEED * timeDelta;
    m_tiltAngle -= PLAYER_TILT_SPEED * timeDelta;
    movingAside = true;
  }

  if (input->isActionKeyPressed(PLAYER_ACTION_MOVE_RIGHT))
  {
    moveVec.x = PLAYER_SPEED * timeDelta;
    m_tiltAngle += PLAYER_TILT_SPEED * timeDelta;
    movingAside = true;
  }

  if (!movingAside)
  {
    float rot = abs(m_tiltAngle) * PLAYER_TILT_SPEED * timeDelta * 0.05f;

    if (m_tiltAngle > 0.01f)
      m_tiltAngle -= rot;
    else if (m_tiltAngle < 0.01f)
      m_tiltAngle += rot;
  } else {
    m_tiltAngle = glm::clamp(m_tiltAngle, -PLAYER_TILT_MAX_ANGLE, PLAYER_TILT_MAX_ANGLE);
  }

  m_shootTimer += timeDelta;
  m_heat -= PLAYER_WEAPON_COOLDOWN_RATE * timeDelta;
  if (m_heat < 0.0f)
    m_heat = 0.0f;

  if (input->isActionKeyPressed(PLAYER_ACTION_FIRE))
    shoot();

  m_position += moveVec;
  m_position.x = glm::clamp(
      m_position.x,
      -PLAYER_HORIZONTAL_POSITION_THRESHOLD,
      PLAYER_HORIZONTAL_POSITION_THRESHOLD);
  m_position.y = glm::clamp(
      m_position.y,
      -PLAYER_VERTICAL_POSITION_THRESHOLD,
      PLAYER_VERTICAL_POSITION_THRESHOLD);

  m_sparkTimer += timeDelta;
  if (moveVec.y != 0.0f && m_sparkTimer > 0.005f)
  {
    m_sparkTimer = 0.0f;
    emitSparks(0.15f);
    emitSparks(-0.15f);
  }

  Spaceship::update(timeDelta);
}

void Player::emitSparks(float align)
{
  ParticleSystem *particleSystem = getScene()->getParticleSystem();
  for (int i = 0; i < 7; i++)
  {
    Particle *particle = particleSystem->emitParticle();

    particle->texture = m_sparkTexture;
    particle->position = m_position + glm::vec3(align, -0.3f, 0.0f);
    particle->life = 1.0f;
    particle->agingRate = 0.8f;
    particle->velocity = glm::vec3(
        randomFloatInterval(-0.3f, 0.3f),
        randomFloatInterval(-0.5f, -1.0f),
        0.0f);
    particle->size = glm::vec2(0.015f, 0.015f);
    particle->color = glm::vec4(1.0f, 1.0f, 1.0f, 0.7f);
  }
}

void Player::shoot()
{
  if (m_shootTimer < PLAYER_SHOOT_RATE || m_heat >= 1.0f)
    return;

  m_heat += PLAYER_WEAPON_HEATING_RATE;
  if (m_heat >= 1.0f)
  {
    m_heat = 1.0f;
    return;
  }

  getScene()->getAudioEngine()->playSound(m_shotSound);

  m_shootTimer = 0;

  Projectile *projectile = new Projectile(getScene(), m_position, 90.0f, this);
  getScene()->attachNode(projectile);
}
