#pragma once

#include <vector>
#include <string>
#include <d3d11.h>
#include <wrl.h>

#include <array>

#include <engine/D3DObjects/Device.h>
#include <engine/D3DObjects/Pipeline/Buffers/Buffer.h>
#include <engine/D3DObjects/Pipeline/Views/SRV.h>



class ResourceManager
{
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	//Initialization and instance can be same function since it has no input parameters
	static ResourceManager* Instance();

	~ResourceManager() = default;

	//Create vertex buffers
	bool addVertexBuffer(const std::string& name, D3D11_SUBRESOURCE_DATA* data, D3D11_USAGE usage, int size);
	bool addVertexBuffer(const std::string& name, void* data, D3D11_USAGE usage, int size);

	// Create constant buffers
	bool addConstantBuffer(const std::string& name, D3D11_SUBRESOURCE_DATA* data, bool dynamic, int size);
	bool addConstantBuffer(const std::string& name, void* data, bool dynamic, int size);

	//Create structured buffers (template for the type of data passed in)
	template<typename T>
	bool addStructuredBuffer(const std::string& name, D3D11_SUBRESOURCE_DATA* data, D3D11_USAGE usage, int size);
	template<typename T>
	bool addStructuredBuffer(const std::string& name, void* data, D3D11_USAGE usage, int size);

	//Create Resource views
	template <typename T>
	bool addShaderResourceView(const std::string& name, const std::string& resourceName, D3D11_SHADER_RESOURCE_VIEW_DESC* desc);

	//Get vertex buffers
	Buffer<VertexBuffer>* getVertexBuffer(const std::string& name);
	Buffer<VertexBuffer>* getVertexBuffer(int index);

	//Get Constant buffers
	Buffer<ConstantBuffer>* getConstantBuffer(const std::string& name);
	Buffer<ConstantBuffer>* getConstantBuffer(int index);

	//Get structured buffers
	Buffer<StructuredBuffer>* getStructuredBuffer(const std::string& name);
	Buffer<StructuredBuffer>* getStructuredBuffer(int index);

	//Get Shader resource views
	SRV* getShaderResourceView(const std::string& name);
	SRV* getShaderResourceView(const int index);

	//Get buffer indexs
	int getVertexBufferIndex(const std::string& name);
	int getConstantBufferIndex(const std::string& name);
	int getStructuredBufferIndex(const std::string& name);

	//Get view indexs
	int getShaderResourceViewIndex(const std::string& name);
protected:
	ResourceManager() = default;

	static ResourceManager* instance;

	//Vectors for buffers
	std::vector<Buffer<VertexBuffer>> VertexBuffers;
	std::vector<Buffer<ConstantBuffer>> ConstantBuffers;
	std::vector<Buffer<StructuredBuffer>> StructuredBuffers;

	//Vectors for Views
	std::vector<SRV> ShaderResourceViews;
};

//These need to be defined in the header, since they are templates
template<typename T>
inline bool ResourceManager::addStructuredBuffer(const std::string& name, D3D11_SUBRESOURCE_DATA* data, D3D11_USAGE usage, int size)
{
	D3D11_BUFFER_DESC desc{};
	desc.ByteWidth = size;
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	desc.StructureByteStride = sizeof(T);
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.Usage = usage;
	
	desc.CPUAccessFlags = usage == D3D11_USAGE_STAGING ? D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE : 0;
	desc.CPUAccessFlags = usage == D3D11_USAGE_DYNAMIC ? D3D11_CPU_ACCESS_WRITE : 0;

	ComPtr<ID3D11Buffer> buffer;
	HRESULT errorCode = Device::Instance()->getDevice()->CreateBuffer(&desc, data, &buffer);
	if (FAILED(errorCode))
	{
		std::cerr << "Error: Structured buffer could not be created\n";
		return false;
	}
	
	StructuredBuffers.emplace_back(name, buffer, usage);
}

template<typename T>
inline bool ResourceManager::addStructuredBuffer(const std::string& name, void* data, D3D11_USAGE usage, int size)
{
	D3D11_SUBRESOURCE_DATA dat{};
	dat.pSysMem = data;
	return addStructuredBuffer<T>(name, &dat, usage, size);
}

