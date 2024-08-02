#include "ResourceManager.h"
#include "ResourceManager.h"
#include "ResourceManager.h"
#include "ResourceManager.h"
#include "ResourceManager.h"
#include "ResourceManager.h"
#include "ResourceManager.h"

#include <iostream>



ResourceManager* ResourceManager::instance = nullptr;

ResourceManager* ResourceManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new ResourceManager();
	}

	return instance;
}



bool ResourceManager::addVertexBuffer(const std::string& name, D3D11_SUBRESOURCE_DATA* data, D3D11_USAGE usage, int size)
{
	D3D11_BUFFER_DESC desc{};
	desc.ByteWidth = size;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.Usage = usage;

	if (usage == D3D11_USAGE_DEFAULT || usage == D3D11_USAGE_STAGING)
	{
		desc.BindFlags |= D3D11_BIND_STREAM_OUTPUT;
	}

	desc.CPUAccessFlags = usage == D3D11_USAGE_STAGING ? D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE : 0;
	desc.CPUAccessFlags = usage == D3D11_USAGE_DYNAMIC ? D3D11_CPU_ACCESS_WRITE : 0;

	ComPtr<ID3D11Buffer> vertexBuffer;

	HRESULT errorCode = Device::Instance()->getDevice()->CreateBuffer(&desc, data, &vertexBuffer);
	if (FAILED(errorCode))
	{
		std::cerr << "Error: failed to create vertex buffer\n";
		return false;
	}

	VertexBuffers.emplace_back(name, vertexBuffer, usage);
	return true;
}

bool ResourceManager::addVertexBuffer(const std::string& name, void* data, D3D11_USAGE usage, int size)
{
	D3D11_SUBRESOURCE_DATA dat{};
	dat.pSysMem = data;

	return addVertexBuffer(name, &dat, usage, size);
}

bool ResourceManager::addConstantBuffer(const std::string& name, D3D11_SUBRESOURCE_DATA* data, bool dynamic, int size)
{
	if (size % 16 != 0)
	{
		std::cerr << "Error: Constant buffer not sized properly, must pack within 16 byte chunks\n";
		return false;
	}

	//Create buffer description
	D3D11_BUFFER_DESC desc{};
	desc.ByteWidth = size;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	desc.Usage = dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_IMMUTABLE;
	desc.CPUAccessFlags = dynamic ? D3D11_CPU_ACCESS_WRITE : 0;

	ComPtr<ID3D11Buffer> constantBuffer;

	HRESULT errorCode = Device::Instance()->getDevice()->CreateBuffer(&desc, data, &constantBuffer);
	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create constant buffer\n";
		return false;
	}


		//Add constant buffer to vector
		//cBuffers.emplace_back(name, constantBuffer,dynamic);
		ConstantBuffers.emplace_back(name, constantBuffer, dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_IMMUTABLE);
	return true;
}

bool ResourceManager::addConstantBuffer(const std::string& name, void* data, bool dynamic, int size)
{
	D3D11_SUBRESOURCE_DATA dat{};
	dat.pSysMem = data;

	return addConstantBuffer(name, &dat, dynamic, size);
}

//Creating templates for each data type a SRV is bound to
template<>
bool ResourceManager::addShaderResourceView<StructuredBuffer>(const std::string& name, const std::string& resourceName, D3D11_SHADER_RESOURCE_VIEW_DESC* desc)
{
	int bufferIndex = getStructuredBufferIndex(resourceName);
	//Error message already printed
	if (bufferIndex == -1)
	{
		return false;
	}
	Buffer<StructuredBuffer>* buffer = getStructuredBuffer(bufferIndex);

	ComPtr<ID3D11ShaderResourceView> SRV;
	HRESULT errorCode = Device::Instance()->getDevice()->CreateShaderResourceView(buffer->getBuffer().Get(), desc, &SRV);
	if (FAILED(errorCode))
	{
		std::cerr << "Error: Failed to create SRV\n";
		return false;
	}

	ShaderResourceViews.emplace_back(name, SRV);
	return true;
}


Buffer<VertexBuffer>* ResourceManager::getVertexBuffer(const std::string& name)
{
	int index = getVertexBufferIndex(name);
	if (index == -1)
	{
		//Error message already printed
		return nullptr;
	}
	return getVertexBuffer(index);
}

Buffer<VertexBuffer>* ResourceManager::getVertexBuffer(int index)
{
	//If index is out of bounds, return null
	if (index < 0 || index >= VertexBuffers.size()) { std::cerr << "Error, index out of range\n"; return nullptr; }
	return &VertexBuffers.at(index);
}

Buffer<ConstantBuffer>* ResourceManager::getConstantBuffer(const std::string& name)
{
	int index = getConstantBufferIndex(name);
	if (index == -1)
	{
		return nullptr;
	}
	return getConstantBuffer(index);
}

Buffer<ConstantBuffer>* ResourceManager::getConstantBuffer(int index)
{
	//If index is out of bounds, return null
	if (index < 0 || index >= ConstantBuffers.size()) { std::cerr << "Error, index out of range\n"; return nullptr; }
	return &ConstantBuffers.at(index);
}

Buffer<StructuredBuffer>* ResourceManager::getStructuredBuffer(const std::string& name)
{
	int index = getStructuredBufferIndex(name);
	if (index == -1)
	{
		return nullptr;
	}
	return getStructuredBuffer(index);
}

Buffer<StructuredBuffer>* ResourceManager::getStructuredBuffer(int index)
{
	if (index < 0 || index >= StructuredBuffers.size())
	{
		std::cerr << "Error: Index is out of range\n";
		return nullptr;
	}
	return &StructuredBuffers.at(index);
}

SRV* ResourceManager::getShaderResourceView(const std::string& name)
{
	int index = getShaderResourceViewIndex(name);
	if (index == -1)
	{
		return nullptr;
	}

	return getShaderResourceView(index);
}

SRV* ResourceManager::getShaderResourceView(const int index)
{
	if (index < 0 || index >= ShaderResourceViews.size())
	{
		std::cerr << "Error: Index is out of range\n";
		return nullptr;
	}
	return &ShaderResourceViews.at(index);
}

int ResourceManager::getVertexBufferIndex(const std::string& name)
{
	//Find vertex buffer in vector
	for (int i = 0; i < VertexBuffers.size(); ++i)
	{
		if (VertexBuffers.at(i).getName() == name)
		{
			return i;
		}
	}
	//Buffer not found
	std::cerr << "Error: Vertex buffer " << name << " not found\n";
	return -1;
}

int ResourceManager::getConstantBufferIndex(const std::string& name)
{
	//Locate constant buffer with name "name"
	for (int i = 0; i < ConstantBuffers.size(); ++i)
	{
		if (ConstantBuffers.at(i).getName() == name)
		{
			return i;
		}
	}
	//CBuffer not found
	std::cerr << "Error: CBuffer " << name << " not found\n";
	return -1;
}

int ResourceManager::getStructuredBufferIndex(const std::string& name)
{
	//Locate constant buffer with name "name"
	for (int i = 0; i < StructuredBuffers.size(); ++i)
	{
		if (StructuredBuffers.at(i).getName() == name)
		{
			return i;
		}
	}
	//CBuffer not found
	std::cerr << "Error: StructuredBuffer " << name << " not found\n";
	return -1;
}

int ResourceManager::getShaderResourceViewIndex(const std::string& name)
{
	//Locate constant buffer with name "name"
	for (int i = 0; i < ShaderResourceViews.size(); ++i)
	{
		if (ShaderResourceViews.at(i).getName() == name)
		{
			return i;
		}
	}
	//CBuffer not found
	std::cerr << "Error: StructuredBuffer " << name << " not found\n";
	return -1;
}
