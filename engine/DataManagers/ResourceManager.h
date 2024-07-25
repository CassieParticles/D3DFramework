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

	//Create vertex buffers
	bool addVertexBuffer(std::string name, D3D11_SUBRESOURCE_DATA* data, D3D11_USAGE usage, int size);
	bool addVertexBuffer(std::string name, void* data, D3D11_USAGE usage, int size);

	// Create constant buffers
	bool addConstantBuffer(std::string name, D3D11_SUBRESOURCE_DATA* data, bool dynamic, int size);
	bool addConstantBuffer(std::string name, void* data, bool dynamic, int size);

	//Get vertex buffers
	Buffer<VertexBuffer>* getVertexBuffer(std::string name);
	Buffer<VertexBuffer>* getVertexBuffer(int index);

	//Get Constant buffers
	Buffer<ConstantBuffer>* getConstantBuffer(std::string name);
	Buffer<ConstantBuffer>* getConstantBuffer(int index);

	//Get buffer IDs
	int getVertexBufferID(const std::string& name);
	int getConstantBufferID(const std::string& name);
protected:
	ResourceManager() = default;

	static ResourceManager* instance;

	std::vector<Buffer<VertexBuffer>> VertexBuffers;
	std::vector<Buffer<ConstantBuffer>> ConstantBuffers;
};