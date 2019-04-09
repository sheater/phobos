#include <stdlib.h>

#include "utils.h"

float randomFloatInterval(float min, float max)
{
  return min + ((rand() % 10000) / 10000.0f * (max - min));
}
