#pragma once

#include <wrl.h>
#include <string>
#include <d3d11.h>

class CBuffer
{
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	CBuffer(const std::string& name, ComPtr<ID3D11Buffer> buffer);
	~CBuffer() = default;

	void addBuffer(const std::string& name, ComPtr<ID3D11Buffer> buffer);

	void bindBuffer(int stagesBoundTo, unsigned int sRegister);

	//TODO: Add better way of writing to constant buffer
	ComPtr<ID3D11Buffer>& getBuffer() { return buffer; }
	const std::string& getName() { return name; }
protected:
	std::string name;
	ComPtr<ID3D11Buffer> buffer;
};