#pragma once

#include <engine/D3DObjects/Pipeline/Shader.h>

#include <vector>
#include <string>

class ShaderManager
{
public:
	static ShaderManager* instance;

	static ShaderManager* Instance();

	bool addVertexShader(const std::string& name, const std::wstring& filePath);
	bool addPixelShader(const std::string& name, const std::wstring& filePath);

	Shader<VERTEX_SHADER>* getVertexShader(const std::string& name);
	Shader<PIXEL_SHADER>* getPixelShader(const std::string& name);

	bool vertexShaderExists(const std::string& name);
	bool pixelShaderExists(const std::string& name);

protected:

	std::vector<Shader<VERTEX_SHADER>*> vertexShaders;
	std::vector<Shader<PIXEL_SHADER>*> pixelShaders;

};