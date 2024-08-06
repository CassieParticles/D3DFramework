#include "SRV.h"

#include <engine/D3DObjects/Pipeline/PipelineStages.h>
#include <engine/D3DObjects/Device.h>

SRV::SRV(const std::string& name, ComPtr<ID3D11ShaderResourceView> view)
{
	this->name = name;
	this->view = view;
}

void SRV::bindView(int shaderStages, unsigned int bindRegister)
{
	Device* device = Device::Instance();
	if (shaderStages & Shaders::VERTEX_SHADER)
	{
		device->getDeviceContext()->VSSetShaderResources(bindRegister, 1, view.GetAddressOf());
	}
	if (shaderStages & Shaders::HULL_SHADER)
	{
		device->getDeviceContext()->HSSetShaderResources(bindRegister, 1, view.GetAddressOf());
	}
	if (shaderStages & Shaders::DOMAIN_SHADER)
	{
		device->getDeviceContext()->DSSetShaderResources(bindRegister, 1, view.GetAddressOf());
	}
	if (shaderStages & Shaders::GEOMETRY_SHADER)
	{
		device->getDeviceContext()->GSSetShaderResources(bindRegister, 1, view.GetAddressOf());
	}
	if (shaderStages & Shaders::PIXEL_SHADER)
	{
		device->getDeviceContext()->PSSetShaderResources(bindRegister, 1, view.GetAddressOf());
	}
}
