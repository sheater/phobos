#pragma once

#include <AL/al.h>

#include "Asset.h"

class Sound : public Asset
{
public:
  Sound(int format, int size, int freq, unsigned char *data);
  ~Sound();

  void play();

private:
  ALuint m_buffer;
};
