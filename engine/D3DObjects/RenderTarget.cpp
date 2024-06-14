#include "RenderTarget.h"

#include <iostream>

#include <engine/D3DObjects/D3DDevice.h>

void RenderTarget::addRTV(ComPtr<ID3D11Texture2D> texture, DirectX::XMFLOAT4 clearColour)
{
	if (RTVCount >= D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT)
	{
		std::cout << "Maximum number of render targets bound already\n";
		return;
	}
	std::cout << "1\n";

	D3DDevice* device = D3DDevice::Instance();
	std::cout << "2\n";
	
	ComPtr<ID3D11RenderTargetView> rtv;

	HRESULT errorCode = device->getDevice()->CreateRenderTargetView(texture.Get(), 0, &rtv);

	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create render target view from texture\n";
		return;
	}

	std::cout << "3\n";
	RTVs[RTVCount] = rtv;
	renderTextures[RTVCount] = texture;
	clearColours[RTVCount][0] = clearColour.x;
	clearColours[RTVCount][1] = clearColour.y;
	clearColours[RTVCount][2] = clearColour.z;
	clearColours[RTVCount][3] = clearColour.w;
	++RTVCount;
	std::cout << "4\n";
}

void RenderTarget::addDSV(ComPtr<ID3D11Texture2D> texture, float defaultDepth, float defaultStencil)
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

	HRESULT errorCode = D3DDevice::Instance()->getDevice()->CreateDepthStencilView(texture.Get(), &depthStencilViewDesc, &DSV);

	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create depth stencil view\n";
		return;
	}
}

void RenderTarget::clear()
{
	D3DDevice* device = D3DDevice::Instance();
	
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
	D3DDevice::Instance()->getDeviceContext()->OMSetRenderTargets(RTVCount, tempArr, DSV.Get());
}
