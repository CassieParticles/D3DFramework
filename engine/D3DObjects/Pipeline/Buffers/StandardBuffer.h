#pragma once

#include <wrl.h>
#include <string>
#include <d3d11.h>

class StandardBuffer
{
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	StandardBuffer(const std::string& name, ComPtr<ID3D11Buffer> buffer, bool dynamic);
	~StandardBuffer() = default;
protected:
	std::string name;
	ComPtr<ID3D11Buffer> buffer;
	bool dynamic;
};