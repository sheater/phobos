#include <FreeImage.h>

#include "TextureLoader.h"
#include "Texture.h"

bool TextureLoader::isSuitableExtension(const std::string &extension)
{
  return extension == "jpg" || extension == "jpeg" || extension == "png";
}

Asset *TextureLoader::loadAsset(const std::string &path)
{
  FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(path.c_str(), 0);
  FIBITMAP *bitmap = FreeImage_Load(fif, path.c_str());

  FIBITMAP *pImage = FreeImage_ConvertTo32Bits(bitmap);
  unsigned int nWidth = FreeImage_GetWidth(pImage);
  unsigned int nHeight = FreeImage_GetHeight(pImage);

  // FIXME: create by renderer
  Texture *texture = new Texture(nWidth, nHeight, (void *)FreeImage_GetBits(pImage));

  FreeImage_Unload(pImage);

  return texture;
  // return nullptr;
}
