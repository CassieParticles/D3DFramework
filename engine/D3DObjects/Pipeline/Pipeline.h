#include <d3d11.h>
#include <string>
#include <wrl.h>

#include <engine/D3DObjects/VertexLayout.h>

class Pipeline
{
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	Pipeline();
	~Pipeline();

	bool addVertexShader(const std::wstring& verexShaderPath);
	bool addFragmentShader(const std::wstring& fragmentShaderPath);

	//TODO: add function once vertex layout works
	//bool addLayoutDescription(Vertexlayout& layout);
protected:

};