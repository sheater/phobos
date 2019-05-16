#include "WaveLoader.h"
#include "Sound.h"

struct RIFFHeader
{
  char riff[4];
  unsigned int size;
  char wave[4];

  void Print()
  {
    printf("RIFFHeader::Print()\n");
    printf("riff: %c%c%c%c\n", riff[0], riff[1], riff[2], riff[3]);
    printf("size: %i\n", size);
    printf("wave: %c%c%c%c\n", wave[0], wave[1], wave[2], wave[3]);
    printf("\n");
  }
};

struct WAVSubChunk1
{
  char subChunkId[4];
  unsigned int subChunkSize;
  short format;
  short numChannels;
  unsigned int sampleRate;
  unsigned int byteRate;
  short blockAlign;
  short bitsPerSample;

  void Print()
  {
    printf("WAVSubChunk1::Print()\n");
    printf("subChunkId: %c%c%c%c\n", subChunkId[0], subChunkId[1], subChunkId[2], subChunkId[3]);
    printf("subChunkSize: %i\n", subChunkSize);
    printf("format: %i\n", format);
    printf("numChannels: %i\n", numChannels);
    printf("sampleRate: %i\n", sampleRate);
    printf("byteRate: %i\n", byteRate);
    printf("blockAlgin: %i\n", blockAlign);
    printf("bitsPerSample: %i\n", bitsPerSample);
    printf("\n");
  }
};

struct WAVSubChunk2
{
  char subChunkId[4];
  unsigned int subChunkSize;

  void Print()
  {
    printf("WAVSubChunk2::Print()\n");
    printf("subChunkId: %c%c%c%c\n", subChunkId[0], subChunkId[1], subChunkId[2], subChunkId[3]);
    printf("subChunkSize: %i\n", subChunkSize);
    printf("\n");
  }
};

bool WaveLoader::isSuitableExtension(const std::string &extension)
{
  return extension == "wav";
}

Asset *WaveLoader::loadAsset(const std::string &path)
{
  FILE *fp = nullptr;
  unsigned char *data = nullptr;
  RIFFHeader riff;
  WAVSubChunk1 chunk1;
  WAVSubChunk2 chunk2;
  int format;

  fp = fopen(path.c_str(), "rb");
  if (!fp)
    throw std::runtime_error("Unable to open file: " + path);

  fread(&riff, sizeof(RIFFHeader), 1, fp);
  fread(&chunk1, sizeof(WAVSubChunk1), 1, fp);
  fread(&chunk2, sizeof(WAVSubChunk2), 1, fp);

  // riff.Print();
  // chunk1.Print();
  // chunk2.Print();

  if (riff.riff[0] != 'R' || riff.riff[1] != 'I' || riff.riff[2] != 'F' || riff.riff[3] != 'F')
    throw std::runtime_error("Invalid 'RIFF' header: " + path);

  if (riff.wave[0] != 'W' || riff.wave[1] != 'A' || riff.wave[2] != 'V' || riff.wave[3] != 'E')
    throw std::runtime_error("Invalid 'WAVE' header: " + path);

  if (chunk1.subChunkId[0] != 'f' || chunk1.subChunkId[1] != 'm' || chunk1.subChunkId[2] != 't' || chunk1.subChunkId[3] != ' ')
    throw std::runtime_error("Invalid 'fmt' header: " + path);

  if (chunk2.subChunkId[0] != 'd' || chunk2.subChunkId[1] != 'a' || chunk2.subChunkId[2] != 't' || chunk2.subChunkId[3] != 'a')
    throw std::runtime_error("Invalid 'data' header: " + path);

  data = new unsigned char[chunk2.subChunkSize];
  fread(data, 1, chunk2.subChunkSize, fp);

  if (chunk1.numChannels == 1)
  {
    if (chunk1.bitsPerSample == 8)
      format = AL_FORMAT_MONO8;
    if (chunk1.bitsPerSample == 16)
      format = AL_FORMAT_MONO16;
  }
  else if (chunk1.numChannels == 2)
  {
    if (chunk1.bitsPerSample == 8)
      format = AL_FORMAT_STEREO8;
    if (chunk1.bitsPerSample == 16)
      format = AL_FORMAT_STEREO16;
  }
  else
    throw std::runtime_error("Unsupported number of channels");

  Sound *sound = new Sound(format, chunk2.subChunkSize, chunk1.sampleRate, data);
  delete data;

  return sound;
}
