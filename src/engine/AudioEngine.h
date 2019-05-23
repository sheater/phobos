#pragma once

#include <AL/al.h>
#include <AL/alc.h>

#include "Sound.h"

class AudioEngine
{
public:
  AudioEngine();
  ~AudioEngine();

  void playSound(Sound *sound);
  void update();

private:
  ALCcontext *m_context;
  ALCdevice *m_device;

  std::map<ALuint, Sound *> m_channels;
};
