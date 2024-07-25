#include "CBufferManager.h"

#include <iostream>

#include <engine/D3DObjects/Device.h>

CBufferManager* CBufferManager::instance = nullptr;

CBufferManager* CBufferManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new CBufferManager();
	}

	return instance;
}

bool CBufferManager::addCBuffer(std::string name, D3D11_SUBRESOURCE_DATA* data, bool dynamic, int size)
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

bool CBufferManager::addCBuffer(std::string name, void* data, bool dynamic, int size)
{
	D3D11_SUBRESOURCE_DATA dat{};
	dat.pSysMem = data;

	return addCBuffer(name, &dat, dynamic, size);
}

Buffer<ConstantBuffer>* CBufferManager::getCBuffer(std::string name)
{
	//Locate constant buffer with name "name"
	for (int i = 0; i < ConstantBuffers.size(); ++i)
	{
		if (ConstantBuffers.at(i).getName() == name)
		{
			return &ConstantBuffers.at(i);
		}
	}
	//CBuffer not found
	std::cerr << "Error: CBuffer " << name << " not found\n";
	return nullptr;
}

Buffer<ConstantBuffer>* CBufferManager::getCBuffer(int index)
{
	//If index is out of bounds, return null
	if (index < 0 || index >= ConstantBuffers.size()) { std::cerr << "Error, index out of range\n"; return nullptr; }
	return &ConstantBuffers.at(index);
}

int CBufferManager::getCBufferID(std::string name)
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
