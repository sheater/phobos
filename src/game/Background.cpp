#include <glm/glm.hpp>

#include "../engine/Scene.h"
#include "../engine/ParticleSystem.h"
#include "../engine/Texture.h"
#include "../engine/utils.h"
#include "Background.h"

Background::Background(Scene *scene) : SceneNode(scene)
{
  ParticleSystem *particleSystem = getScene()->getParticleSystem();
  AssetsManager *assetsMgr = getScene()->getAssetsManager();
  Texture *starTexture = static_cast<Texture *>(assetsMgr->getAsset("assets/textures/star.png"));

  for (int i = 0; i < NUM_BACKGROUND_LAYERS; i++)
  {
    BackgroundLayer layer;

    layer.speed = (i + 1) * 1.0f;

    for (int j = 0; j < NUM_BACKGROUND_LAYER_STARS; j++)
    {
      Particle *particle = particleSystem->emitParticle();
      particle->position = glm::vec3(
          randomFloatInterval(-BACKGROUND_HORIZONTAL_THRESHOLD, BACKGROUND_HORIZONTAL_THRESHOLD),
          randomFloatInterval(-BACKGROUND_VERTICAL_THRESHOLD, BACKGROUND_VERTICAL_THRESHOLD),
          -6.0f);
      particle->size = glm::vec2(BACKGROUND_STAR_SIZE, BACKGROUND_STAR_SIZE);
      particle->color = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);
      particle->texture = starTexture;
      layer.stars.push_back(particle);
    }

    m_layers.push_back(layer);
  }
}

void Background::update(float timeDelta)
{
  for (
      std::vector<BackgroundLayer>::iterator it = m_layers.begin();
      it != m_layers.end();
      it++)
  {
    for (
        std::vector<Particle *>::iterator pit = it->stars.begin();
        pit != it->stars.end();
        pit++)
    {
      glm::vec3 &position = (*pit)->position;
      position.y -= timeDelta * it->speed;
      if (position.y < -BACKGROUND_VERTICAL_THRESHOLD)
      {
        position.y = BACKGROUND_VERTICAL_THRESHOLD;
      }
    }
  }
}
