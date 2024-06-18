#pragma once

#include <string>
#include <d3d11.h>
#include <dxgi1_3.h>
#include <wrl.h>
#include <DirectXMath.h>

class RenderTarget
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	RenderTarget() = default;
	~RenderTarget() = default;

	void addRTV(const ComPtr<ID3D11Texture2D>& texture,DirectX::XMFLOAT4 clearColour);

	void addDSV(const ComPtr<ID3D11Texture2D>& texture, float defaultDepth, float defaultStencil);
	//TODO: Add function to create texture as well

	void clear();
	void bind();
	
protected:
	//Render target views
	ComPtr<ID3D11RenderTargetView> RTVs[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT]{};
	ComPtr<ID3D11Texture2D> renderTextures[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT]{};
	float clearColours[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT][4]{};
	int RTVCount{};

	//Depth stencil views
	ComPtr<ID3D11DepthStencilView> DSV{};
	ComPtr<ID3D11Texture2D> depthStencilTexture{};
	float defaultDepth{};
	char defaultStencil{};
};