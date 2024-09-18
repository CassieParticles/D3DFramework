#include "ShaderManager.h"

ShaderManager* ShaderManager::instance = nullptr;

ShaderManager* ShaderManager::getInstance()
{
	if (!instance)
	{
		instance = new ShaderManager();
	}

	return instance;
}

void ShaderManager::addVertexShader(const std::string& name, const std::wstring& filePath)
{
	vertexShaders.emplace_back( name,filePath );
}

void ShaderManager::addPixelShader(const std::string& name, const std::wstring& filePath)
{
	pixelShaders.emplace_back(name, filePath);
}

Shader<VERTEX_SHADER>* ShaderManager::getVertexShader(const std::string& name)
{
	for (int i = 0; i < vertexShaders.size(); ++i)
	{
		if (vertexShaders.at(i).getName() == name)
		{
			return &vertexShaders.at(i);
		}
	}
}

Shader<PIXEL_SHADER>* ShaderManager::getPixelShader(const std::string& name)
{
	for (int i = 0; i < pixelShaders.size(); ++i)
	{
		if (pixelShaders.at(i).getName() == name)
		{
			return &pixelShaders.at(i);
		}
	}
}

