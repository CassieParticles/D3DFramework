#include "CBuffer.h"

#include <iostream>

#include <engine/D3DObjects/Device.h>
#include <engine/D3DObjects/Pipeline/PipelineStages.h>


CBuffer::CBuffer(const std::string& name, ComPtr<ID3D11Buffer> buffer, bool dynamic)
{
	addBuffer(name, buffer, dynamic);
}

void CBuffer::addBuffer(const std::string& name, ComPtr<ID3D11Buffer> buffer, bool dynamic)
{
	this->name = name;
	this->buffer = buffer;
	this->dynamic = dynamic;
}


//TODO: Add better way of binding cBuffers
void CBuffer::bindBuffer(int stagesBoundTo, unsigned int sRegister)
{
	Device* device = Device::Instance();
	if (stagesBoundTo & Shaders::VERTEX_SHADER)
	{
		device->getDeviceContext()->VSSetConstantBuffers(sRegister, 1, buffer.GetAddressOf());
	}
	if (stagesBoundTo & Shaders::HULL_SHADER)
	{
		device->getDeviceContext()->HSSetConstantBuffers(sRegister, 1, buffer.GetAddressOf());
	}
	if (stagesBoundTo & Shaders::DOMAIN_SHADER)
	{
		device->getDeviceContext()->DSSetConstantBuffers(sRegister, 1, buffer.GetAddressOf());
	}
	if (stagesBoundTo & Shaders::GEOMETRY_SHADER)
	{
		device->getDeviceContext()->GSSetConstantBuffers(sRegister, 1, buffer.GetAddressOf());
	}
	if (stagesBoundTo & Shaders::PIXEL_SHADER)
	{
		device->getDeviceContext()->PSSetConstantBuffers(sRegister, 1, buffer.GetAddressOf());
	}
}

void CBuffer::updateCBuffer(void* data, int size)
{
	if (!dynamic)
	{
		std::cerr << "Error: buffer is not dynmaic\n";
		return;
	}

	Device* device = Device::Instance();

	D3D11_MAPPED_SUBRESOURCE map;

	device->getDeviceContext()->Map(buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
	memcpy(map.pData, data, size);
	device->getDeviceContext()->Unmap(buffer.Get(), 0);
}
