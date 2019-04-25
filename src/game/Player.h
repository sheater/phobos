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

class Player : public Spaceship
{
private:
  float m_tiltAngle;
  float m_sparkTimer;
  float m_shootTimer;
  float m_heat;
  unsigned int m_score;
  Texture *m_sparkTexture;

public:
  Player(Scene *scene);

  static glm::mat4 getPreprocessTransform();

  inline float getWeaponHeat() { return m_heat; }
  inline unsigned int getScore() { return m_score; }
  inline void addScore(unsigned int amount) { m_score += amount; }

  void update(float timeDelta);

  void emitSparks(float align);
  void shoot();
};
