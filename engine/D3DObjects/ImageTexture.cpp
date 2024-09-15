#include "ImageTexture.h"

#include <iostream>

#include <engine/DataManagers/AssetLoader.h>
#include <engine/D3DObjects/Device.h>

ImageTexture::ImageTexture(ImageData* imageData): imageData{imageData}
{
	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = imageData->width;
	desc.Height = imageData->height;
	desc.MipLevels= 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_IMMUTABLE; 
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA dat{};
	dat.pSysMem = imageData->data;
	dat.SysMemPitch = imageData->width * 4;

	HRESULT errorCode = Device::Instance()->getDevice()->CreateTexture2D(&desc, &dat, &texture);
	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create texture\n";
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Texture2D.MostDetailedMip = 0;

	errorCode = Device::Instance()->getDevice()->CreateShaderResourceView(texture.Get(), &srvDesc, &SRV);

	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create SRV\n";
	}
}

ImageTexture::~ImageTexture()
{
}
