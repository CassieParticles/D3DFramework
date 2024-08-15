#pragma once

#include <wrl.h>
#include <d3d11.h>
#include <string>

class Texture2D
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	Texture2D(const std::string& name, ComPtr<ID3D11Texture2D> texture, D3D11_USAGE usage);
	~Texture2D() = default;

	const std::string& getName() { return name; }
	ComPtr<ID3D11Texture2D> getTexture() { return texture; }
protected:
	std::string name;
	ComPtr<ID3D11Texture2D> texture;
	D3D11_USAGE usage;
};