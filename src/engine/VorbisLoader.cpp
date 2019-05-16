#include <AL/al.h>
#include <iostream>

#include "VorbisLoader.h"
#include "Sound.h"

#define BUFFER_SIZE 4096

bool VorbisLoader::isSuitableExtension(const std::string &extension)
{
  return extension == "ogg";
}

Asset *VorbisLoader::loadAsset(const std::string &path)
{
  int endian = 0;
  int bitStream;
  int bytes;
  char array[BUFFER_SIZE];
  std::vector<unsigned char> buffer;
  ALenum format;

  FILE *fp = fopen(path.c_str(), "rb");
  if (!fp)
    throw std::runtime_error("Unable to read: " + path);

  vorbis_info *pInfo;
  OggVorbis_File oggFile;

  ov_open(fp, &oggFile, NULL, 0);
  pInfo = ov_info(&oggFile, -1);

  if (pInfo->channels == 1)
    format = AL_FORMAT_MONO16;
  else
    format = AL_FORMAT_STEREO16;

  do
  {
    bytes = ov_read(&oggFile, array, BUFFER_SIZE, endian, 2, 0, &bitStream);
    if (bytes < 0) {
      ov_clear(&oggFile);
      throw std::runtime_error("Error while decoding: " + path);
    }

    buffer.insert(buffer.end(), array, array + bytes);
  } while (bytes > 0);

  ov_clear(&oggFile);

  std::cout << "Rate: " << (int)pInfo->rate << std::endl;
  std::cout << "Size: " << buffer.size() << std::endl;

  // return new Sound(format, static_cast<ALsizei>(buffer.size()), pInfo->rate, static_cast<unsigned char*>(buffer[0]));
  // return new Sound(format, static_cast<ALsizei>(buffer.size()), (int)pInfo->rate, &buffer[0]);
  return new Sound(format, static_cast<ALsizei>(buffer.size()), 22000, &buffer[0]);
}
