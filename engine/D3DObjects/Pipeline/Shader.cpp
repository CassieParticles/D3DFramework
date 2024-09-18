#include "Shader.h"

#include <iostream>
#include <d3dcompiler.h>


bool compileShader(const std::wstring& filePath, Microsoft::WRL::ComPtr<ID3DBlob>& shaderByteCode, const std::string& profile, const std::string& entryFunction)
{
	constexpr UINT compileFlags = D3DCOMPILE_ENABLE_STRICTNESS;

	Microsoft::WRL::ComPtr<ID3DBlob> tempShaderBlob = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

	HRESULT errorCode = D3DCompileFromFile(filePath.data(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryFunction.data(), profile.data(), compileFlags, 0, &tempShaderBlob, &errorBlob);
	if (FAILED(errorCode))
	{
		if (errorCode == 0x80070003)
		{
			std::cerr << "Failed to find shader at path specified\n";
		}
		if (errorBlob != nullptr)
		{
			std::cerr << "Compilation message" << static_cast<const char*>(errorBlob->GetBufferPointer()) << "\n";
		}
		return false;
	}
	shaderByteCode = std::move(tempShaderBlob);
	return true;
}

Shader<VERTEX_SHADER>::Shader(const std::string& name, const std::wstring& filePath) : name{ name }
{
	Device* device = Device::Instance();
	if (compileShader(filePath, byteCode, "vs_5_0", "Main"))
	{
		if (FAILED(device->getDevice()->CreateVertexShader(byteCode->GetBufferPointer(), byteCode->GetBufferSize(), nullptr, &shader)))
		{
			std::cerr << "Failed to create shader\n";
		}
	}
}

Shader<PIXEL_SHADER>::Shader(const std::string& name, const std::wstring& filePath) : name{ name }
{
	Device* device = Device::Instance();
	ComPtr<ID3DBlob> byteCode{};
	if (compileShader(filePath, byteCode, "ps_5_0", "Main"))
	{
		if (FAILED(device->getDevice()->CreatePixelShader(byteCode->GetBufferPointer(), byteCode->GetBufferSize(), nullptr, &shader)))
		{
			std::cerr << "Failed to create shader\n";
		}
	}
}