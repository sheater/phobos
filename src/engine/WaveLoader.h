#pragma once

#include "Loader.h"

class WaveLoader : public Loader
{
  bool isSuitableExtension(const std::string &extension);
  Asset *loadAsset(const std::string &path);
};
