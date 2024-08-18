#include <d3d11.h>
#include <string>
#include <wrl.h>
#include <vector>

#include <engine/D3DObjects/Pipeline/VertexLayout.h>
#include <engine/D3DObjects/Pipeline/RasterizerState.h>
#include <engine/D3DObjects/Pipeline/CBuffer.h>
#include <engine/D3DObjects/Pipeline/PipelineStages.h>

class Pipeline
{
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	Pipeline() = default;
	~Pipeline() = default;

	//Adding shaders
	void addVertexShader(const std::wstring& vertexShaderPath) { this->vertexShaderPath = vertexShaderPath; }
	void addPixelShader(const std::wstring& pixelShaderPath) { this->pixelShaderPath = pixelShaderPath; }

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

	ComPtr<ID3D11VertexShader> vertexShader{};
	ComPtr<ID3D11PixelShader> pixelShader{};
	ComPtr<ID3DBlob> VSByteCode{};

	D3D11_PRIMITIVE_TOPOLOGY primitiveType{};

	VertexLayout vertexLayout{};
	RasterizerState rasterizerState{};

	std::vector<CBufferBinding> CBuffers;
};