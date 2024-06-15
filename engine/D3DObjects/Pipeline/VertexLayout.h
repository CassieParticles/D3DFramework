#pragma once

#include <vector>
#include <wrl.h>
#include <d3d11.h>

class VertexLayout
{
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	VertexLayout() = default;
	~VertexLayout() = default;

	void addVertexComponent(D3D11_INPUT_ELEMENT_DESC element);

	bool createLayout(ComPtr<ID3DBlob> byteCode);

	void bind();
protected:
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;

	ComPtr<ID3D11InputLayout> layout;
};