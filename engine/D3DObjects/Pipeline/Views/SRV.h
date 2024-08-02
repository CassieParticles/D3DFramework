#pragma once

#include <wrl.h>
#include <string>
#include <d3d11.h>



class SRV
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	SRV(const std::string& name, ComPtr<ID3D11ShaderResourceView> view);
	~SRV() = default;

	void bindView(int shaderStages, unsigned int bindRegister);

	const std::string& getName() { return name; }
	ComPtr<ID3D11ShaderResourceView> getSRV() { return view; }
protected:
	std::string name;
	ComPtr<ID3D11ShaderResourceView> view;
};