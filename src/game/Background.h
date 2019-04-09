#pragma once

#include <vector>

#include "../engine/Particle.h"
#include "../engine/SceneNode.h"

#define NUM_BACKGROUND_LAYERS 3
#define NUM_BACKGROUND_LAYER_STARS 30

#define BACKGROUND_STAR_SIZE 0.05
#define BACKGROUND_HORIZONTAL_THRESHOLD 3.5f
#define BACKGROUND_VERTICAL_THRESHOLD 3.0f

typedef struct
{
  float speed;
  std::vector<Particle *> stars;
} BackgroundLayer;

class Background : public SceneNode
{
public:
  Background(Scene *scene);
  void update(float timeDelta);

private:
  std::vector<BackgroundLayer> m_layers;
};
