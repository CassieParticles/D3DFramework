#pragma once

#include <engine/D3DObjects/ImageTexture.h>
#include <string>
#include <unordered_map>

class AssetLoader
{
public:
	static AssetLoader* Instance();

	//Get texture, and load it if it doesn't exist
	ImageTexture* getTexture(const std::string& imagePath);
protected:
	static AssetLoader* instance;

	AssetLoader() = default;
	~AssetLoader();

	ImageData* loadImageData(const std::string& imagePath);

	std::unordered_map<std::string, ImageTexture*> textureMap;
	std::vector<std::string> loadedTextures;
};