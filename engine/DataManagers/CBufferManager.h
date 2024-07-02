#pragma once

#include <vector>
#include <string>
#include <d3d11.h>
#include <wrl.h>

#include <engine/D3DObjects/Pipeline/CBuffer.h>

class CBufferManager
{
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	CBufferManager() = default;
	~CBufferManager() = default;

	// Create constant buffers
	bool addBuffer(std::string name, D3D11_SUBRESOURCE_DATA* data, bool dynamic, int size);
	bool addBuffer(std::string name, void* data, bool dynamic, int size);

	const CBuffer* getCBuffer(std::string name);
	const CBuffer* getCBuffer(int index);
protected:
	std::vector<CBuffer> cBuffers;
};