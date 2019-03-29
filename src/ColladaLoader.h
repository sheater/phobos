#pragma once

#include <string>

#include "Loader.h"

class ColladaLoader: public Loader {
  bool isSuitableExtension(const std::string& extension);
  virtual Asset *loadAsset(const std::string &path);
};
