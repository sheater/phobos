#pragma once

#include <string>
#include <map>
#include <glm/gtc/matrix_transform.hpp>

#include "../engine/ModelNode.h"
#include "../engine/MeshNode.h"
#include "../engine/utils.h"
#include "../engine/Texture.h"

#define EXPLOSION_PARTICLE_SPEED 0.8f

typedef struct
{
  float direction;
  float distance;
} MeshExplosionState;

enum SpaceshipState
{
  SPACESHIP_STATE_ALIVE = 0,
  SPACESHIP_STATE_EXPLOSION,
};

class Spaceship : public ModelNode
{
public:
  Spaceship(
      Scene *scene,
      const std::string &path,
      const glm::mat4 &preprocessTransformMatrix)
      : ModelNode(scene, path, preprocessTransformMatrix)
  {
    m_position = glm::vec3(0.0f, 0.0f, -5.0f);
    m_direction = 0.0f;
    m_tiltAngle = 0.0f;
    m_state = SPACESHIP_STATE_ALIVE;

    AssetsManager *assetsMgr = getScene()->getAssetsManager();
    m_explosionTexture = static_cast<Texture *>(assetsMgr->getAsset("assets/textures/explosion.png"));
  }

  void update(float timeDelta)
  {
    localTransform = glm::translate(glm::mat4(1.0f), m_position);
    localTransform = glm::rotate(
        localTransform,
        glm::radians(m_direction),
        glm::vec3(0.0f, 0.0f, 1.0f));
    localTransform = glm::rotate(
        localTransform,
        glm::radians(m_tiltAngle),
        glm::vec3(0.0f, 1.0f, 0.0f));

    if (m_state == SPACESHIP_STATE_EXPLOSION)
    {
      for (
        std::map<MeshNode*, MeshExplosionState>::iterator it = m_explosionState.begin();
        it != m_explosionState.end();
        it++
      )
      {
        MeshExplosionState* es = &it->second;
        float explosionSpeed = 250.0f * timeDelta;
        float dx = cos(glm::radians(es->direction)) * explosionSpeed;
        float dy = sin(glm::radians(es->direction)) * explosionSpeed;

        MeshNode* mesh = it->first;

        mesh->localTransform = glm::translate(
          mesh->localTransform,
          glm::vec3(dx, dy, -4.0f * explosionSpeed));

        mesh->material->opacity -= explosionSpeed * 0.002f;
      }
    }

    ModelNode::update(timeDelta);
  }

  void explode()
  {
    if (m_state == SPACESHIP_STATE_EXPLOSION)
      return;

    delete m_collisionHull;
    m_collisionHull = nullptr;
    m_state = SPACESHIP_STATE_EXPLOSION;
    m_explosionDuration = 0.0f;

    for (
      std::vector<SceneNode*>::iterator it = m_nodes.begin();
      it != m_nodes.end();
      it++)
    {
      MeshNode* mesh = dynamic_cast<MeshNode *>(*it);
      if (!mesh)
        continue;

      MeshExplosionState es;
      es.direction = randomFloatInterval(0.0f, 360.0f);
      m_explosionState.insert(std::pair<MeshNode*, MeshExplosionState>(mesh, es));
    }

    ParticleSystem *particleSystem = getScene()->getParticleSystem();
    for (int i = 0; i < 30; i++)
    {
      Particle *particle = particleSystem->emitParticle();

      particle->texture = m_explosionTexture;
      particle->position = m_position;
      particle->life = 1.0f;
      particle->agingRate = 0.8f;
      particle->velocity = glm::vec3(
          randomFloatInterval(-EXPLOSION_PARTICLE_SPEED, EXPLOSION_PARTICLE_SPEED),
          randomFloatInterval(-EXPLOSION_PARTICLE_SPEED, EXPLOSION_PARTICLE_SPEED),
          randomFloatInterval(-EXPLOSION_PARTICLE_SPEED, EXPLOSION_PARTICLE_SPEED));
      particle->size = glm::vec2(0.03f, 0.03f);
      particle->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }
  }

protected:
  float m_tiltAngle;
  float m_direction;
  glm::vec3 m_position;
  SpaceshipState m_state;

  float m_explosionDuration;
  std::map<MeshNode*, MeshExplosionState> m_explosionState;
  Texture* m_explosionTexture;
};
