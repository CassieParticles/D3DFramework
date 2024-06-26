#include "RenderTarget.h"

#include <iostream>

#include <engine/D3DObjects/Device.h>

void RenderTarget::addRTV(const ComPtr<ID3D11Texture2D>& texture, DirectX::XMFLOAT4 clearColour)
{
	if (RTVCount >= D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT)
	{
		std::cout << "Maximum number of render targets bound already\n";
		return;
	}

	Device* device = Device::Instance();
	
	ComPtr<ID3D11RenderTargetView> rtv;

	HRESULT errorCode = device->getDevice()->CreateRenderTargetView(texture.Get(), 0, &rtv);

	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create render target view from texture\n";
		return;
	}

	RTVs[RTVCount] = rtv;
	renderTextures[RTVCount] = texture;
	clearColours[RTVCount][0] = clearColour.x;
	clearColours[RTVCount][1] = clearColour.y;
	clearColours[RTVCount][2] = clearColour.z;
	clearColours[RTVCount][3] = clearColour.w;
	++RTVCount;
}

void RenderTarget::addDSV(const ComPtr<ID3D11Texture2D>& texture, float defaultDepth, float defaultStencil)
{
	if (DSV != nullptr)
	{
		std::cout << "Depth stencil view already exists\n";
	}
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
	depthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Flags = 0;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	HRESULT errorCode = Device::Instance()->getDevice()->CreateDepthStencilView(texture.Get(), &depthStencilViewDesc, &DSV);

	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create depth stencil view\n";
		return;
	}

	this->defaultDepth = defaultDepth;
	this->defaultStencil = defaultStencil;
}

void RenderTarget::clear()
{
	Device* device = Device::Instance();
	
	for (int i = 0; i < RTVCount; ++i)
	{
		device->getDeviceContext()->ClearRenderTargetView(RTVs[i].Get(), clearColours[i]);
	}

	device->getDeviceContext()->ClearDepthStencilView(DSV.Get(), D3D11_CLEAR_DEPTH, defaultDepth, defaultStencil);
}

void RenderTarget::bind()
{
	ID3D11RenderTargetView* tempArr[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT]{};
	for (int i = 0; i < RTVCount; ++i)
	{
		tempArr[i] = RTVs->Get();
	}
	Device::Instance()->getDeviceContext()->OMSetRenderTargets(RTVCount, tempArr, DSV.Get());
}
