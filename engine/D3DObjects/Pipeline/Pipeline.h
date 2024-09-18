#pragma once

#include <d3d11.h>
#include <string>
#include <wrl.h>
#include <vector>

#include <engine/D3DObjects/Pipeline/VertexLayout.h>
#include <engine/D3DObjects/Pipeline/RasterizerState.h>
#include <engine/D3DObjects/Pipeline/CBuffer.h>
#include <engine/D3DObjects/Pipeline/PipelineStages.h>
#include <engine/D3DObjects/Pipeline/Shader.h>

class Pipeline
{
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	Pipeline() = default;
	~Pipeline() = default;

	//Adding shaders
	void addVertexShader(const std::string& name);
	void addPixelShader(const std::string& name);

	void setPrimitiveType(D3D_PRIMITIVE_TOPOLOGY primitiveType) { this->primitiveType = primitiveType; }

	void addVertexComponent(D3D11_INPUT_ELEMENT_DESC desc) { vertexLayout.addVertexComponent(desc); }
	D3D11_RASTERIZER_DESC& getRastierizerDesc() { return rasterizerState.getDesc(); }

	void bindConstantBuffer(const std::string& name, int stagesBound, int cRegister);
	void bindConstantBuffer(int ID, int stagesBound, int cRegister) { CBuffers.push_back({ ID,stagesBound,cRegister }); }

	bool compilePipeline();

	void bind();
protected:
	bool compileShader(const std::wstring& filePath, ComPtr<ID3DBlob>& shaderByteCode, const std::string& profile, const std::string& entryFunction);

	bool usable{};

	//Shader paths, stored to be compiled
	std::wstring vertexShaderPath{};
	std::wstring pixelShaderPath{};

	Shader<VERTEX_SHADER>* vertexShader{};
	Shader<PIXEL_SHADER>* pixelShader{};


	D3D11_PRIMITIVE_TOPOLOGY primitiveType{};

	VertexLayout vertexLayout{};
	RasterizerState rasterizerState{};

	std::vector<CBufferBinding> CBuffers;
};