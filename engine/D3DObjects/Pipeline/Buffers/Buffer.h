#pragma once

#include <wrl.h>
#include <string>
#include <d3d11.h>
#include <iostream>

#include <engine/D3DObjects/Pipeline/PipelineStages.h>

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
	Buffer(const std::string& name, Comptr<ID3D11Buffer> buffer, Usage usage) { addBuffer(name, buffer, usage); }

	void bindBuffer(int stagesBoundTo, unsigned int bRegister) { std::cerr << "Error: Unknown buffer type\n"; }
protected:
	void addBuffer(const std::string& name, Comptr<ID3D11Buffer> buffer, Usage usage)
	{
		this->name = name;
		this->buffer = buffer;
		this->usage = usage;
	}

	std::string name;
	ComPtr<ID3D11Buffer> buffer;
	Usage usage;
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
