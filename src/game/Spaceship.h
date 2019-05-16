#pragma once

#include <string>
#include <map>
#include <glm/gtc/matrix_transform.hpp>

#include "../engine/ModelNode.h"
#include "../engine/MeshNode.h"
#include "../engine/utils.h"
#include "../engine/Texture.h"
#include "../engine/Sound.h"

#define EXPLOSION_PARTICLE_SPEED 0.8f

typedef struct
{
  float direction;
  float distance;
} MeshExplosionState;

enum SpaceshipState
{
  SPACESHIP_STATE_ACTIVE = 0,
  SPACESHIP_STATE_IDLE,
  SPACESHIP_STATE_EXPLOSION,
};

class Spaceship : public ModelNode
{
public:
  Spaceship(
      Scene *scene,
      const std::string &path,
      const glm::mat4 &preprocessTransformMatrix);

  void update(float timeDelta);
  void explode();

protected:
  float m_tiltAngle;
  float m_direction;
  glm::vec3 m_position;
  SpaceshipState m_state;

  float m_explosionDuration; // FIXME: useless for now
  std::map<MeshNode *, MeshExplosionState> m_explosionState;
  Texture *m_explosionTexture;
  Sound *m_explosionSound;
};
