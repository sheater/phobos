#include <iostream>

#include "Sound.h"

Sound::Sound(int format, int size, int freq, unsigned char *data)
{
  alGenBuffers(1, &m_buffer);
  alBufferData(m_buffer, format, data, size, freq);
}

Sound::~Sound()
{
  std::cout << "Sound::~Sound()" << std::endl;
  alDeleteBuffers(1, &m_buffer);
}
