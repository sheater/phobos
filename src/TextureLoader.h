#pragma once

#include <string>

#include "Loader.h"

class TextureLoader: public Loader {
  bool isSuitableExtension(const std::string& extension);
  Asset *loadAsset(const std::string &path);
};
