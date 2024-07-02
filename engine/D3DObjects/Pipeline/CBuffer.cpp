#include "CBuffer.h"
#include <engine/D3DObjects/Device.h>
#include <engine/D3DObjects/Pipeline/PipelineStages.h>

CBuffer::CBuffer(const std::string& name, ComPtr<ID3D11Buffer> buffer)
{
	addBuffer(name, buffer);
}

void CBuffer::addBuffer(const std::string& name, ComPtr<ID3D11Buffer> buffer)
{
	this->name = name;
	this->buffer = buffer;
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