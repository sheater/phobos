#include <iostream>

#include "../engine/utils.h"
#include "../engine/BoundingBox.h"
#include "Spaceship.h"
#include "Projectile.h"

#define PLAYER_SPEED 2.0f
#define PLAYER_VERTICAL_POSITION_THRESHOLD 1.8f
#define PLAYER_HORIZONTAL_POSITION_THRESHOLD 2.2f
#define PLAYER_TILT_SPEED 1.0f
#define PLAYER_TILT_MAX_ANGLE -45.0f
#define PLAYER_SHOOT_RATE 0.25f
#define PLAYER_WEAPON_HEATING_RATE 0.1f
#define PLAYER_WEAPON_COOLDOWN_RATE 0.2f

enum PlayerKeyboardActions
{
  PLAYER_ACTION_MOVE_UP = 0,
  PLAYER_ACTION_MOVE_DOWN,
  PLAYER_ACTION_MOVE_LEFT,
  PLAYER_ACTION_MOVE_RIGHT,
  PLAYER_ACTION_FIRE,
};

class Player : public Spaceship
{
private:
  float m_tiltAngle;
  float m_sparkTimer;
  float m_shootTimer;
  float m_heat;
  Texture *m_sparkTexture;

public:
  Player(Scene *scene)
      : Spaceship(scene, "assets/models/spaceship2/model.dae", getPreprocessTransform())
  {
    m_sparkTimer = 0.0f;
    m_shootTimer = 0.0f;
    m_heat = 0.0f;

    AssetsManager *assetsMgr = getScene()->getAssetsManager();
    m_sparkTexture = static_cast<Texture *>(assetsMgr->getAsset("assets/textures/spark.png"));
  }

  static glm::mat4 getPreprocessTransform()
  {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.08f, 0.0f, 0.0f));

    transform = glm::rotate(
        transform, glm::radians(90.0f),
        glm::vec3(0.0f, 0.0f, 1.0f));

    return glm::scale(transform, glm::vec3(0.0012f));
    // return glm::scale(transform, glm::vec3(0.01f));
  }

  inline float getWeaponHeat() { return m_heat; }

  void update(float timeDelta)
  {
    glm::vec3 moveVec(0.0f);
    InputHandler *input = getScene()->getInputHandler();

    if (input->isActionKeyPressed(PLAYER_ACTION_MOVE_UP))
      moveVec.y = PLAYER_SPEED * timeDelta;

    if (input->isActionKeyPressed(PLAYER_ACTION_MOVE_DOWN))
      moveVec.y = -PLAYER_SPEED * timeDelta;

    if (input->isActionKeyPressed(PLAYER_ACTION_MOVE_LEFT))
      moveVec.x = -PLAYER_SPEED * timeDelta;

    if (input->isActionKeyPressed(PLAYER_ACTION_MOVE_RIGHT))
      moveVec.x = PLAYER_SPEED * timeDelta;

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

  void emitSparks(float align)
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

  void shoot()
  {
    if (m_shootTimer < PLAYER_SHOOT_RATE || m_heat >= 1.0f)
      return;

    m_heat += PLAYER_WEAPON_HEATING_RATE;
    if (m_heat >= 1.0f) {
      m_heat = 1.0f;
      return;
    }

    m_shootTimer = 0;

    Projectile *projectile = new Projectile(getScene(), m_position, 90.0f, this);
    getScene()->attachNode(projectile);
  }
};
