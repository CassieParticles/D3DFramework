#include "RasterizerState.h"

#include <iostream>

#include <engine/D3DObjects/Device.h>

RasterizerState::RasterizerState()
{
	//Set default values
	desc =
	{
	D3D11_FILL_SOLID,	//Fill mode solid
	D3D11_CULL_BACK,	//Cull back faces
	false,				//CCW faces aren't front faces
	0,					//Depth bias
	0,					//Depth bias clamp
	0,					//SlopeScaledDepthBias
	true,				//Clip pixels based on depth
	false,				//Disable scissor test
	false,				//Disable multisampling
	false				//Disable antialiasedLines
	};
}

RasterizerState::RasterizerState(D3D11_RASTERIZER_DESC desc):desc{desc}
{
}

bool RasterizerState::createState()
{
	HRESULT err = Device::Instance()->getDevice()->CreateRasterizerState(&desc, &rasterizerState);
	if (FAILED(err))
	{
		std::cerr << "Failed to create rasterizer state\n";
		return false;
	}
	return true;
}

void RasterizerState::bind()
{
	Device::Instance()->getDeviceContext()->RSSetState(rasterizerState.Get());
}
