#pragma once

#include <wrl.h>
#include <d3d11.h>
#include <string>

class TextureSampler
{
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	TextureSampler(const std::string& name, ComPtr<ID3D11SamplerState> sampler);
	~TextureSampler() = default;
protected:
	std::string name;
	ComPtr<ID3D11SamplerState> sampler;
};