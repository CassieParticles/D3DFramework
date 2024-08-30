#pragma once

#define NOMINMAX
#include <wrl.h>
#include <d3d11.h>
#include <engine/D3DObjects/Pipeline/Pipeline.h>

//Class used to render a texture to the whole screen
class RenderScreen
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	static RenderScreen* Instance();

	void renderTexture(ComPtr<ID3D11ShaderResourceView>& textureSRV);
protected:
	static RenderScreen* instance;

	RenderScreen();
	~RenderScreen() = default;

	ComPtr<ID3D11Buffer> vertexPosition;
	ComPtr<ID3D11Buffer> vertexUV;
	ComPtr<ID3D11Buffer> indices;

	Pipeline pipeline;

	ComPtr<ID3D11SamplerState> textureSampler;
};