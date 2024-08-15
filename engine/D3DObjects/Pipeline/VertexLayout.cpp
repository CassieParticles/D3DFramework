#include "VertexLayout.h"

#include <iostream>
#include <engine/D3DObjects/Device.h>

void VertexLayout::addVertexComponent(D3D11_INPUT_ELEMENT_DESC element)
{
	inputLayoutDesc.push_back(element);
}

bool VertexLayout::createLayout(ComPtr<ID3DBlob> byteCode)
{
	HRESULT errorCode = Device::Instance()->getDevice()->CreateInputLayout(inputLayoutDesc.data(), inputLayoutDesc.size(), byteCode->GetBufferPointer(), byteCode->GetBufferSize(), &layout);
	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create input layout\n";
		return false;
	}
	return true;
}

void VertexLayout::bind()
{
	Device::Instance()->getDeviceContext()->IASetInputLayout(layout.Get());
}
