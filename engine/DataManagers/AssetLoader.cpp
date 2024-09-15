#include "AssetLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

AssetLoader* AssetLoader::instance = nullptr;

AssetLoader* AssetLoader::Instance()
{
    if (!instance)
    {
        instance = new AssetLoader();
    }

    return instance;
}

ImageTexture* AssetLoader::getTexture(const std::string& imagePath)
{
    ImageTexture* image = textureMap[imagePath];
    if (!image)
    {
        image = textureMap[imagePath] = new ImageTexture(loadImageData(imagePath));
    }
    return image;
}



AssetLoader::~AssetLoader()
{
    for (auto it = loadedTextures.begin(); it != loadedTextures.end(); it++)
    {
        delete textureMap[*it];
    }
}

ImageData* AssetLoader::loadImageData(const std::string& imagePath)
{
    ImageData* data = new ImageData;

    data->data = stbi_load(imagePath.c_str(), &data->width, &data->height, nullptr, 4);

    return data;
}