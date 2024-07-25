#pragma once

#include <wrl.h>
#include <string>
#include <d3d11.h>
#include <iostream>

#include <engine/D3DObjects/Pipeline/PipelineStages.h>
#include <engine/D3DObjects/Device.h>

#include "BufferTypes.h"

template <typename T>
class Buffer
{
	template<typename S>
	using ComPtr = Microsoft::WRL::ComPtr<S>;
public:
	enum Usage : char
	{
		Immutable,
		Default,
		Dynamic,
		Staging
	};
	Buffer(const std::string& name, ComPtr<ID3D11Buffer> buffer, D3D11_USAGE usage) { addBuffer(name, buffer, usage); }

	void bindBuffer(int stagesBoundTo, unsigned int bRegister) { std::cerr << "Error: Unknown buffer type\n"; }

	void updateBuffer(void* data, int size) { std::cout << "Error: Unknown buffer type\n"; }

	ComPtr<ID3D11Buffer>& getBuffer() { return buffer; }
	const std::string& getName() { return name; }
protected:
	void addBuffer(const std::string& name, ComPtr<ID3D11Buffer> buffer, D3D11_USAGE usage)
	{
		this->name = name;
		this->buffer = buffer;
		this->usage = usage;
	}

	std::string name;
	ComPtr<ID3D11Buffer> buffer;
	D3D11_USAGE usage;
};

template<>
void Buffer<ConstantBuffer>::bindBuffer(int stagesBoundTo, unsigned int bRegister)
{
	Device* device = Device::Instance();
	if (stagesBoundTo & Shaders::VERTEX_SHADER)
	{
		device->getDeviceContext()->VSSetConstantBuffers(bRegister, 1, buffer.GetAddressOf());
	}
	if (stagesBoundTo & Shaders::HULL_SHADER)
	{
		device->getDeviceContext()->HSSetConstantBuffers(bRegister, 1, buffer.GetAddressOf());
	}
	if (stagesBoundTo & Shaders::DOMAIN_SHADER)
	{
		device->getDeviceContext()->DSSetConstantBuffers(bRegister, 1, buffer.GetAddressOf());
	}
	if (stagesBoundTo & Shaders::GEOMETRY_SHADER)
	{
		device->getDeviceContext()->GSSetConstantBuffers(bRegister, 1, buffer.GetAddressOf());
	}
	if (stagesBoundTo & Shaders::PIXEL_SHADER)
	{
		device->getDeviceContext()->PSSetConstantBuffers(bRegister, 1, buffer.GetAddressOf());
	}
}

template<>
void Buffer<ConstantBuffer>::updateBuffer(void* data, int size)
{
	//Constant buffer can either be dynamic or immutable
	if (usage != D3D11_USAGE_DYNAMIC)
	{
		std::cerr << "Error: Buffer is not dynamic\n";
		return;
	}

	Device* device = Device::Instance();

	D3D11_MAPPED_SUBRESOURCE map;

	device->getDeviceContext()->Map(buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
	memcpy(map.pData, data, size);
	device->getDeviceContext()->Unmap(buffer.Get(), 0);
}
