#include "Mesh.h"
#include "Mesh.h"
#include "Mesh.h"

#include <iostream>

#include <engine/D3DObjects/Device.h>

void Mesh::addVertexBuffer(ComPtr<ID3D11Buffer> vertexBuffer, int vertexStride, int vertexOffset)
{
	if (bufferCount < D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT)
	{
		vertexBuffers[bufferCount] = vertexBuffer;
		vertexStrides[bufferCount] = vertexStride;
		vertexOffsets[bufferCount] = vertexOffset;
		bufferCount++;
	}
}

void Mesh::addVertexBuffer(D3D11_SUBRESOURCE_DATA* data, bool dynamic, int size, int vertexStride, int vertexOffset)
{
	D3D11_BUFFER_DESC desc;
	desc.ByteWidth = size;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.Usage = dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_IMMUTABLE;
	desc.CPUAccessFlags = dynamic ? D3D11_CPU_ACCESS_WRITE : 0;

	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;

	HRESULT errorCode = Device::Instance()->getDevice()->CreateBuffer(&desc, data, &vertexBuffer);
	if (FAILED(errorCode))
	{
		std::cerr << "Error in creating vertex buffer\n";
		return;
	}

	addVertexBuffer(vertexBuffer, vertexStride, vertexOffset);
}

void Mesh::addVertexBuffer(void* data, bool dynamic, int size, int vertexStride, int vertexOffset)
{
	D3D11_SUBRESOURCE_DATA dat;
	dat.pSysMem = data;
	addVertexBuffer(&dat, dynamic, size, vertexStride, vertexOffset);
}

void Mesh::addIndexBuffer(ComPtr<ID3D11Buffer> indexBuffer, int indexOffset)
{
	this->indexBuffer = indexBuffer;
	this->indexOffset = indexOffset;
}

void Mesh::addIndexBuffer(D3D11_SUBRESOURCE_DATA* data, bool dynamic, int size, int indexOffset)
{
	D3D11_BUFFER_DESC desc;
	desc.ByteWidth = size;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	desc.Usage = dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_IMMUTABLE;
	desc.CPUAccessFlags = dynamic ? D3D11_CPU_ACCESS_WRITE : 0;

	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;

	HRESULT errorCode = Device::Instance()->getDevice()->CreateBuffer(&desc, data, &indexBuffer);
	if (FAILED(errorCode))
	{
		std::cerr << "Error in creating  index buffer\n";
		return;
	}

	addIndexBuffer(indexBuffer, indexOffset);
}

void Mesh::addIndexBuffer(int* data, bool dynamic, int size, int indexOffset)
{
	D3D11_SUBRESOURCE_DATA dat;
	dat.pSysMem = data;
	addIndexBuffer(&dat, dynamic, size, indexOffset);
}

Microsoft::WRL::ComPtr<ID3D11Buffer>& Mesh::getVertexBuffer(int index)
{
	return vertexBuffers[index];
}

Microsoft::WRL::ComPtr<ID3D11Buffer>& Mesh::getIndexBuffer()
{
	return indexBuffer;
}

void Mesh::setBuffers()
{
	ID3D11Buffer* vBufferArray[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT]{};
	for (int i = 0; i < bufferCount; ++i)
	{
		vBufferArray[i] = vertexBuffers[i].Get();
	}

	Device* device = Device::Instance();
	device->getDeviceContext()->IASetVertexBuffers(vertexStartSlot, bufferCount, vBufferArray, vertexStrides, vertexOffsets);
	device->getDeviceContext()->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, indexOffset);
}
