#pragma once

#define NOMINMAX
#include <wrl.h>
#include <d3d11.h>
#include <string>

struct ImageData
{
	int width;
	int height;

	unsigned char* data{};

	~ImageData() { delete[] data; }
};

//This is a class intended to store 
class ImageTexture
{
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	ImageTexture(ImageData* imageData);
	~ImageTexture();

	ComPtr<ID3D11Texture2D>& getTexture() { return texture; }
	ComPtr<ID3D11ShaderResourceView>& getSRV() { return SRV; }
protected:
	ImageData* imageData;

	ComPtr<ID3D11Texture2D> texture;
	ComPtr<ID3D11ShaderResourceView> SRV;
};