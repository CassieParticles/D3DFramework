#include "ShaderManager.h"

#include <iostream>

ShaderManager* ShaderManager::instance = nullptr;

ShaderManager* ShaderManager::Instance()
{
	if (!instance)
	{
		instance = new ShaderManager();
	}

	return instance;
}

bool ShaderManager::addVertexShader(const std::string& name, const std::wstring& filePath)
{
	if (vertexShaderExists(name))
	{
		return false;
	}
	Shader<VERTEX_SHADER>* vertexShader = new Shader<VERTEX_SHADER>{ name, filePath };
	vertexShaders.push_back(vertexShader);
	return true;
}

bool ShaderManager::addPixelShader(const std::string& name, const std::wstring& filePath)
{
	if (pixelShaderExists(name))
	{
		return false;
	}
	Shader<PIXEL_SHADER>* pixelShader = new Shader<PIXEL_SHADER>{ name, filePath };
	pixelShaders.push_back(pixelShader);
	return true;
}

Shader<VERTEX_SHADER>* ShaderManager::getVertexShader(const std::string& name)
{
	for (int i = 0; i < vertexShaders.size(); ++i)
	{
		if (vertexShaders.at(i)->getName() == name)
		{
			return vertexShaders.at(i);
		}
	}
	return nullptr;
}

Shader<PIXEL_SHADER>* ShaderManager::getPixelShader(const std::string& name)
{
	for (int i = 0; i < pixelShaders.size(); ++i)
	{
		if (pixelShaders.at(i)->getName() == name)
		{
			return pixelShaders.at(i);
		}
	}
	return nullptr;
}

bool ShaderManager::vertexShaderExists(const std::string& name)
{
	for (int i = 0; i < vertexShaders.size(); ++i)
	{
		if (vertexShaders.at(i)->getName() == name)
		{
			return true;
		}
	}
	return false;
}

bool ShaderManager::pixelShaderExists(const std::string& name)
{
	for (int i = 0; i < pixelShaders.size(); ++i)
	{
		if (pixelShaders.at(i)->getName() == name)
		{
			return true;
		}
	}
	return false;
}