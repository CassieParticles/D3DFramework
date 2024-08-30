#include "RenderScreen.h"

#include <engine/D3DObjects/Device.h>
#include <DirectXMath.h>

RenderScreen* RenderScreen::instance = nullptr;

RenderScreen* RenderScreen::Instance()
{
	if (instance == nullptr)
	{
		instance = new RenderScreen();
	}
	return instance;
}

void RenderScreen::renderTexture(ComPtr<ID3D11ShaderResourceView>& textureSRV)
{
	ComPtr<ID3D11DeviceContext> deviceContext = Device::Instance()->getDeviceContext();	//Quicker then getting it from the Device every time

	ID3D11Buffer* buffers[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
	UINT offsets[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
	UINT strides[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];

	buffers[0] = vertexPosition.Get();
	offsets[0] = 0;
	strides[0] = sizeof(DirectX::XMFLOAT2);

	buffers[1] = vertexUV.Get();
	offsets[1] = 0;
	strides[1] = sizeof(DirectX::XMFLOAT2);

	for (int i = 2; i < D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT; ++i)
	{
		buffers[i] = nullptr;
		offsets[i] = 0;
		strides[i] = 0;
	}

	deviceContext->IASetVertexBuffers(0, 2, buffers,strides ,offsets );
	deviceContext->IASetIndexBuffer(indices.Get(), DXGI_FORMAT_R32_UINT, 0);

	deviceContext->PSSetShaderResources(0, 1, textureSRV.GetAddressOf());
	deviceContext->PSSetSamplers(0, 1, textureSampler.GetAddressOf());

	pipeline.bind();

	deviceContext->DrawIndexed(6, 0, 0);
}

RenderScreen::RenderScreen()
{
	//Constants for vertices
	constexpr float vertexPos[8]
	{
		-1,-1,	//BL
		-1, 1,	//TL
		 1,-1,	//BR
		 1, 1	//TR
	};

	constexpr float UVs[8]
	{
		0,1,
		0,0,
		1,1,
		1,0
	};

	constexpr int id[6]
	{
		0,1,3,
		0,3,2
	};

	D3D11_BUFFER_DESC desc{};
	D3D11_SUBRESOURCE_DATA dat{};

	//Create vertex position buffer
	desc.ByteWidth = sizeof(vertexPos);
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	
	dat.pSysMem = vertexPos;

	Device::Instance()->getDevice()->CreateBuffer(&desc, &dat, &vertexPosition);

	//Create vertex UV buffer
	desc.ByteWidth = sizeof(UVs);
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	dat.pSysMem = UVs;

	Device::Instance()->getDevice()->CreateBuffer(&desc, &dat, &vertexUV);

	//Create index buffer

	desc.ByteWidth = sizeof(id);
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	dat.pSysMem = id;

	Device::Instance()->getDevice()->CreateBuffer(&desc, &dat, &indices);

	//Create the texture sampler
	D3D11_SAMPLER_DESC sDesc{};

	sDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sDesc.MipLODBias = 0;
	sDesc.MaxAnisotropy = 1;
	sDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sDesc.BorderColor[0] = 1.f;
	sDesc.BorderColor[1] = 1.f;
	sDesc.BorderColor[2] = 1.f;
	sDesc.BorderColor[3] = 1.f;
	sDesc.MinLOD = -FLT_MAX;
	sDesc.MaxLOD = FLT_MAX;

	Device::Instance()->getDevice()->CreateSamplerState(&sDesc, &textureSampler);

	//Set up and compile pipeline
	pipeline.addVertexShader(L"shaders/EngineShaders/RenderScreen/vertex.hlsl");
	pipeline.addPixelShader(L"shaders/EngineShaders/RenderScreen/fragment.hlsl");

	pipeline.setPrimitiveType(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	pipeline.addVertexComponent({ "POSITION",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 });
	pipeline.addVertexComponent({ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,1,0,D3D11_INPUT_PER_VERTEX_DATA,0 });

	pipeline.compilePipeline();

	
}
