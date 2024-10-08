#include "Pipeline.h"

#include <iostream>
#include <d3dcompiler.h>

#include <engine/D3DObjects/Device.h>
#include <engine/DataManagers/CBufferManager.h>
#include <engine/DataManagers/ShaderManager.h>

void Pipeline::addVertexShader(const std::string& name)
{
	vertexShader = ShaderManager::Instance()->getVertexShader(name);
}

void Pipeline::addPixelShader(const std::string& name)
{
	pixelShader = ShaderManager::Instance()->getPixelShader(name);
}

void Pipeline::bindConstantBuffer(const std::string& name, int stagesBound, int cRegister)
{
	int ID = CBufferManager::Instance()->getCBufferID(name);
	if (ID == -1) { return; }

	bindConstantBuffer(ID, stagesBound, cRegister);
}

bool Pipeline::compilePipeline()
{
	Device* device = Device::Instance();

	

	//Create input layout (must be done after vertex shader is compiled)
	vertexLayout.createLayout(vertexShader->getByteCode());
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
	CBufferManager* cBufferManager = CBufferManager::Instance();
	
	//Bind fixed function stages
	vertexLayout.bind();
	rasterizerState.bind();

	//Set primitive topology
	device->getDeviceContext()->IASetPrimitiveTopology(primitiveType);

	//Bind shader stages
	vertexShader->bindShader();
	pixelShader->bindShader();

	//Bind the constant buffers
	for(int i=0;i<CBuffers.size();++i)
	{
		CBufferBinding binding = CBuffers.at(i);
		cBufferManager->getCBuffer(binding.BufferID)->bindBuffer(binding.StagesBound, binding.cRegister);
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
		if (errorCode == 0x80070003)
		{
			std::cerr << "Failed to find shader at path specified";
		}
		return false;
	}
	shaderByteCode = std::move(tempShaderBlob);
	return true;
}