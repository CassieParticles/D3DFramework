#include "ResourceManager.h"

#include <iostream>

#include <engine/D3DObjects/Device.h>

ResourceManager* ResourceManager::instance = nullptr;

ResourceManager* ResourceManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new ResourceManager();
	}

	return instance;
}



bool ResourceManager::addVertexBuffer(std::string name, D3D11_SUBRESOURCE_DATA* data, D3D11_USAGE usage, int size)
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

bool ResourceManager::addVertexBuffer(std::string name, void* data, D3D11_USAGE usage, int size)
{
	D3D11_SUBRESOURCE_DATA dat{};
	dat.pSysMem = data;

	return addVertexBuffer(name, &dat, usage, size);
}

bool ResourceManager::addConstantBuffer(std::string name, D3D11_SUBRESOURCE_DATA* data, bool dynamic, int size)
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

bool ResourceManager::addConstantBuffer(std::string name, void* data, bool dynamic, int size)
{
	D3D11_SUBRESOURCE_DATA dat{};
	dat.pSysMem = data;

	return addConstantBuffer(name, &dat, dynamic, size);
}

Buffer<VertexBuffer>* ResourceManager::getVertexBuffer(std::string name)
{
	int index = getVertexBufferID(name);
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

Buffer<ConstantBuffer>* ResourceManager::getConstantBuffer(std::string name)
{
	int index = getConstantBufferID(name);
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

int ResourceManager::getVertexBufferID(const std::string& name)
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

int ResourceManager::getConstantBufferID(const std::string& name)
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
