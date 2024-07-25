#pragma once

struct CBufferBinding
{
	int BufferID;
	int StagesBound;
	int cRegister;
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
