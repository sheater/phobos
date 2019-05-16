#pragma once

#include <AL/al.h>
#include <AL/alc.h>

class AudioEngine
{
public:
  AudioEngine()
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

    // alGenBuffers(NUM_BUFFERS, g_Buffers);
  }

  ~AudioEngine()
  {
    // alDeleteBuffers(NUM_BUFFERS, g_Buffers);
    // Context=alcGetCurrentContext();
    //Get device for active context
    // m_Device=alcGetContextsDevice(Context);
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);
  }

  // void playSound(Sound* sound)
  // {
  //   unsigned int source;

  //   alGenSources(1, &source);
  //   alSourcei(alSource, AL_BUFFER, alSampleSet)
  //   alSourcePlay(source);
  // }

// do {
//     // Query the state of the souce
//     alGetSourcei(sourceID, AL_SOURCE_STATE, &state);
//   } while (state != AL_STOPPED);
  // void update() {
  //   for (std::)
  // }

private:
  ALCcontext *m_context;
  ALCdevice *m_device;

  // std::map<unsigned int, Sound*> m_channels;
  // std::vector<> m_channels;
};
