#pragma once

#include <AL/al.h>

#include "Asset.h"

class Sound : public Asset
{
public:
  Sound(int format, int size, int freq, unsigned char *data);
  ~Sound();

private:
  friend class AudioEngine;

  ALuint m_buffer;
};
