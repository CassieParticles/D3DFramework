#pragma once

#include <vector>
#include <string>
#include <d3d11.h>
#include <wrl.h>

#include <engine/D3DObjects/Pipeline/Buffers/Buffer.h>

class ResourceManager
{
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	//Initialization and instance can be same function since it has no input parameters
	static ResourceManager* Instance();

	~ResourceManager() = default;

	// Create constant buffers
	bool addCBuffer(std::string name, D3D11_SUBRESOURCE_DATA* data, bool dynamic, int size);
	bool addCBuffer(std::string name, void* data, bool dynamic, int size);

	Buffer<ConstantBuffer>* getCBuffer(std::string name);
	Buffer<ConstantBuffer>* getCBuffer(int index);

	int getCBufferID(std::string name);
protected:
	ResourceManager() = default;

	static ResourceManager* instance;

	std::vector<Buffer<ConstantBuffer>> ConstantBuffers;
};