#include <map>

#include "AudioEngine.h"

AudioEngine::AudioEngine()
{
  m_device = alcOpenDevice(nullptr);
  m_context = alcCreateContext(m_device, nullptr);
  alcMakeContextCurrent(m_context);

  ALfloat listenerPos[] = {0.0, 0.0, 0.0};
  ALfloat listenerVel[] = {0.0, 0.0, 0.0};
  ALfloat listenerOri[] = {0.0, 0.0, -1.0, 0.0, 1.0, 0.0};

  alListenerfv(AL_POSITION, listenerPos);
  alListenerfv(AL_VELOCITY, listenerVel);
  alListenerfv(AL_ORIENTATION, listenerOri);
}

AudioEngine::~AudioEngine()
{
  for (std::map<ALuint, Sound *>::iterator it = m_channels.begin(); it != m_channels.end(); it++)
  {
    alSourceStop(it->first);
    alDeleteSources(1, &it->first);
  }

  alcMakeContextCurrent(nullptr);
  alcDestroyContext(m_context);
  alcCloseDevice(m_device);
}

void AudioEngine::playSound(Sound *sound)
{
  ALuint source;

  alGenSources(1, &source);
  alSourcei(source, AL_BUFFER, sound->m_buffer);
  alSourcePlay(source);

  m_channels.insert(std::pair<ALuint, Sound *>(source, sound));
}

void AudioEngine::update()
{
  ALint sourceState;

  for (std::map<ALuint, Sound *>::iterator it = m_channels.begin(); it != m_channels.end(); it++)
  {
    alGetSourcei(it->first, AL_SOURCE_STATE, &sourceState);

    if (sourceState == AL_STOPPED)
    {
      alDeleteSources(1, &it->first);
      m_channels.erase(it->first);
    }
  }
}
