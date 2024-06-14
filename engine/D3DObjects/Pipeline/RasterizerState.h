#pragma once

#include <wrl.h>
#include <d3d11.h>


class RasterizerState
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	RasterizerState();
	RasterizerState(D3D11_RASTERIZER_DESC desc);
	~RasterizerState() = default;

	D3D11_RASTERIZER_DESC& getDesc() { return desc; }

	bool createState();

	void use();
protected:
	D3D11_RASTERIZER_DESC desc{};
	ComPtr<ID3D11RasterizerState> rasterizerState;
};