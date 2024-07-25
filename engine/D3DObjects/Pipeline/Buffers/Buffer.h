#pragma once

#include <wrl.h>
#include <string>
#include <d3d11.h>
#include <iostream>

#include <engine/D3DObjects/Pipeline/PipelineStages.h>
#include <engine/D3DObjects/Device.h>

#include "BufferTypes.h"

template <typename T>
class Buffer
{
	template<typename S>
	using ComPtr = Microsoft::WRL::ComPtr<S>;
public:
	enum Usage : char
	{
		Immutable,
		Default,
		Dynamic,
		Staging
	};
	Buffer(const std::string& name, ComPtr<ID3D11Buffer> buffer, D3D11_USAGE usage) { addBuffer(name, buffer, usage); }

	void bindBuffer(int stagesBoundTo, unsigned int bRegister) { std::cerr << "Error: Unknown buffer type\n"; }

	void updateBuffer(void* data, int size) { std::cout << "Error: Unknown buffer type\n"; }

	ComPtr<ID3D11Buffer>& getBuffer() { return buffer; }
	const std::string& getName() { return name; }
protected:
	void addBuffer(const std::string& name, ComPtr<ID3D11Buffer> buffer, D3D11_USAGE usage)
	{
		this->name = name;
		this->buffer = buffer;
		this->usage = usage;
	}

	std::string name;
	ComPtr<ID3D11Buffer> buffer;
	D3D11_USAGE usage;
};



//Separate parts of the template to make code more readable
#include "ConstantBuffer.h"