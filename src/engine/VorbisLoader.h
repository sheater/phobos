#pragma once

#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

#include "Loader.h"

class VorbisLoader : public Loader
{
  bool isSuitableExtension(const std::string &extension);
  Asset *loadAsset(const std::string &path);
};
