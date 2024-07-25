#include "Pipeline.h"

#include <iostream>
#include <d3dcompiler.h>

#include <engine/D3DObjects/Device.h>
#include <engine/DataManagers/ResourceManager.h>

void Pipeline::bindConstantBuffer(const std::string& name, int stagesBound, int cRegister)
{
	int ID = ResourceManager::Instance()->getConstantBufferID(name);
	if (ID == -1) { return; }

	bindConstantBuffer(ID, stagesBound, cRegister);
}

bool Pipeline::compilePipeline()
{
	Device* device = Device::Instance();

	//Add vertex shader
	if (compileShader(vertexShaderPath, VSByteCode, "vs_5_0", "Main"))
	{
		if (FAILED(device->getDevice()->CreateVertexShader(VSByteCode->GetBufferPointer(), VSByteCode->GetBufferSize(), nullptr, &vertexShader)))
		{
			std::cerr<<"Failed to create vertex shader\n";
			return false;
		}
	}
	//TODO: Add other shader stages

	//Add pixel shader
	ComPtr<ID3DBlob> PSByteCode;
	if (compileShader(pixelShaderPath, PSByteCode, "ps_5_0", "Main"))
	{
		if (FAILED(device->getDevice()->CreatePixelShader(PSByteCode->GetBufferPointer(), PSByteCode->GetBufferSize(), nullptr, &pixelShader)))
		{
			std::cerr<<"Failed to create pixel shader\n";
			return false;
		}
	}

	//Create input layout (must be done after vertex shader is compiled)
	vertexLayout.createLayout(VSByteCode);
	//Create rasterizer state
	rasterizerState.createState();

	return usable = true;
}

void Pipeline::bind()
{
	if (!usable)
	{
		std::cerr << "Error: Pipeline is not usable\n";
		return;
	}
	Device* device = Device::Instance();
	ResourceManager* cBufferManager = ResourceManager::Instance();
	
	//Bind fixed function stages
	vertexLayout.bind();
	rasterizerState.bind();

	//Set primitive topology
	device->getDeviceContext()->IASetPrimitiveTopology(primitiveType);

	//Bind shader stages
	device->getDeviceContext()->VSSetShader(vertexShader.Get(), nullptr, 0);
	device->getDeviceContext()->PSSetShader(pixelShader.Get(), nullptr, 0);

	//Bind the constant buffers
	for(int i=0;i<CBuffers.size();++i)
	{
		CBufferBinding binding = CBuffers.at(i);
		cBufferManager->getConstantBuffer(binding.BufferID)->bindBuffer(binding.StagesBound, binding.cRegister);
	}
}

bool Pipeline::compileShader(const std::wstring& filePath, ComPtr<ID3DBlob>& shaderByteCode, const std::string& profile, const std::string& entryFunction)
{
	constexpr UINT compileFlags = D3DCOMPILE_ENABLE_STRICTNESS;

	ComPtr<ID3DBlob> tempShaderBlob = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;

	HRESULT errorCode = D3DCompileFromFile(filePath.data(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryFunction.data(), profile.data(), compileFlags, 0, &tempShaderBlob, &errorBlob);

	if (FAILED(errorCode))
	{
		std::cerr << "Failed to compile shader\n";
		if (errorBlob != nullptr)
		{
			std::cerr << "Compilation message" << static_cast<const char*>(errorBlob->GetBufferPointer()) << "\n";
		}
		return false;
	}
	shaderByteCode = std::move(tempShaderBlob);
	return true;
}