#pragma once
#include <string>
#include <wrl.h>
#include <d3d11.h>

#include <engine/D3DObjects/Pipeline/PipelineStages.h>
#include <Engine/D3DObjects/Device.h>

template<Shaders T> class Shader{};

template<>
class Shader<VERTEX_SHADER>
{
	template<typename S>
	using ComPtr = Microsoft::WRL::ComPtr<S>;
public:
	Shader(const std::string& name, const std::wstring& filePath);

	const std::string& getName() { return name; }
	ComPtr<ID3DBlob>& getByteCode() { return byteCode; }

	void bindShader() { Device::Instance()->getDeviceContext()->VSSetShader(shader.Get(), nullptr, 0); }
protected:
	const std::string name;

	ComPtr<ID3D11VertexShader> shader;
	ComPtr<ID3DBlob> byteCode;
};

template<>
class Shader<PIXEL_SHADER>
{
	template<typename S>
	using ComPtr = Microsoft::WRL::ComPtr<S>;
public:
	Shader(const std::string& name, const std::wstring& filePath);

	const std::string& getName() { return name; }

	void bindShader() { Device::Instance()->getDeviceContext()->PSSetShader(shader.Get(), nullptr, 0); }
protected:
	const std::string name;

	ComPtr<ID3D11PixelShader> shader;
};