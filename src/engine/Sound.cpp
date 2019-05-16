#include "Sound.h"

Sound::Sound(int format, int size, int freq, unsigned char *data)
{
  alGenBuffers(1, &m_buffer);
  alBufferData(m_buffer, format, data, size, freq);
}

Sound::~Sound()
{
  alDeleteBuffers(1, &m_buffer);
}

void Sound::play()
{
  unsigned int source;

  alGenSources(1, &source);
  alSourcei(source, AL_BUFFER, m_buffer);
  alSourcePlay(source);
}
