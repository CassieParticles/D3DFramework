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

	void addRTV(const ComPtr<ID3D11Texture2D>& texture,DXGI_FORMAT textureFormat, DirectX::XMFLOAT4 clearColour, bool addSRV);
	void addRenderTargetSRV(int index);

	void addDSV(const ComPtr<ID3D11Texture2D>& texture, float defaultDepth, float defaultStencil);
	//TODO: Add function to create texture as well

	void changeClearColour(int index, DirectX::XMFLOAT4 clearColour);

	ComPtr<ID3D11Texture2D>& getRenderTexture(int index) { return renderTextures[index]; }
	ComPtr<ID3D11Texture2D>& getDepthTexture() { return depthStencilTexture; }

	ComPtr<ID3D11ShaderResourceView>& getRenderTargetSRV(int index) { return SRVs[index]; }
	ComPtr<ID3D11ShaderResourceView>& getDepthSRV() { return depthSRV; }

	void clear();
	void bind();
	
protected:
	//Render target views
	ComPtr<ID3D11RenderTargetView> RTVs[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT]{};
	ComPtr<ID3D11ShaderResourceView> SRVs[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT]{};
	ComPtr<ID3D11Texture2D> renderTextures[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT]{};
	float clearColours[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT][4]{};
	DXGI_FORMAT textureFormats[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT]{};
	int RTVCount{};

	//Depth stencil views
	ComPtr<ID3D11DepthStencilView> DSV{};
	ComPtr<ID3D11ShaderResourceView> depthSRV{};
	ComPtr<ID3D11Texture2D> depthStencilTexture{};
	float defaultDepth{};
	char defaultStencil{};
};