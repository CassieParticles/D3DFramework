#include "Window.h"
#include "Window.h"

#include <iostream>
#include <glfw3.h>
#include <d3dcompiler.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <glfw3native.h>

#include <engine/D3DObjects/Device.h>
#include <engine/DataManagers/CBufferManager.h>

Window* Window::instance = nullptr;

Window* Window::InitializeWindow(const std::string& windowTitle, int windowWidth, int windowHeight)
{
	if (instance == nullptr)
	{
		instance = new Window(windowTitle, windowWidth, windowHeight);
	}
	return instance;
}

Window* Window::Instance()
{
	return instance;
}

bool Window::getWindowShouldClose()
{
	return glfwWindowShouldClose(window);
}

void Window::changeBackBufferClearColour(DirectX::XMFLOAT4 newColour)
{
	defaultRenderTarget.changeClearColour(0, newColour);	//Default render target has only one texture
}

void Window::clearBackBuffer()
{
	glfwPollEvents();
	//float clearColour[4] = { colour.x,colour.y,colour.z,colour.w };
	//device->getDeviceContext()->ClearRenderTargetView(renderTargetView.Get(), clearColour);
	//device->getDeviceContext()->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.f, 0.f);

	defaultRenderTarget.clear();
}

void Window::presentBackBuffer()
{
	swapChain->Present(0, DXGI_PRESENT_ALLOW_TEARING);
}

Window::Window(const std::string& windowTitle, int windowWidth, int windowHeight)
{
	createWindow(windowTitle, windowWidth, windowHeight);
}

bool Window::createWindow(const std::string& windowTitle, int windowWidth, int windowHeight)
{
	//Initialize GLFW
	if (!glfwInit())
	{
		std::cerr << "GLFW failed to initialize\n";
		return false;
	}

	//Create the GLFW window
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_FALSE);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	width = windowWidth;
	height = windowHeight;

	window = glfwCreateWindow(width, height, windowTitle.c_str(), nullptr, nullptr);

	if (!window)
	{
		std::cerr << "Failed to create DXGIFactory\n";
		return false;
	}

	//Set up resizing window code to update window object
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, Window::handleResize);

	//Create DXGI factory
	HRESULT errorCode = CreateDXGIFactory1(IID_PPV_ARGS(&factory));
	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create DXGIFactory\n";
		return false;
	}

	device = Device::InitializeDevices();

	//Create swapchain
	//TODO: Allow user to change these
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc
	{
		width,
		height,
		DXGI_FORMAT_B8G8R8A8_UNORM,
		false,
		{1,0},
		DXGI_USAGE_RENDER_TARGET_OUTPUT,
		2,
		DXGI_SCALING_STRETCH,
		DXGI_SWAP_EFFECT_FLIP_DISCARD,
		DXGI_ALPHA_MODE_IGNORE,
		DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING
	};

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullScreenDesc{};
	fullScreenDesc.Windowed = true;

	errorCode = factory->CreateSwapChainForHwnd(device->getDevice().Get(), glfwGetWin32Window(window), &swapChainDesc, &fullScreenDesc, nullptr, &swapChain);
	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create swapchain\n";
		return false;
	}

	errorCode = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer);
	if (FAILED(errorCode))
	{
		std::cerr << "Failed to get backbuffer texture\n";
		return false;
	}

	//Create depth texture
	D3D11_TEXTURE2D_DESC depthTexDesc
	{
		width,
		height,
		1,
		1,
		DXGI_FORMAT_D32_FLOAT,
		{1,0},
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_DEPTH_STENCIL,
		0,
		0
	};

	errorCode = device->getDevice()->CreateTexture2D(&depthTexDesc, 0, &depthBuffer);
	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create depth texture\n";
		return false;
	}

	defaultRenderTarget.addRTV(backBuffer, DXGI_FORMAT_B8G8R8A8_UNORM, DirectX::XMFLOAT4(0, 0, 0, 1.0),false);
	defaultRenderTarget.addDSV(depthBuffer, 1.0, 0.0);

	defaultRenderTarget.changeViewport({ 0,0,static_cast<float>(width),static_cast<float>(height),0,1 });

	//Create render target view
	errorCode = device->getDevice()->CreateRenderTargetView(backBuffer.Get(), 0, &renderTargetView);
	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create render target view\n";
		return false;
	}

	//Create depth stencil view

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
	depthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Flags = 0;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	errorCode = device->getDevice()->CreateDepthStencilView(depthBuffer.Get(), &depthStencilViewDesc, &depthStencilView);

	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create depth stencil view\n";
		return false;
	}

	return true;
}

void Window::setSize(int width, int height)
{
	this->width = width;
	this->height = height;

	int index = CBufferManager::Instance()->getCBufferID("WindowSize");
	if (index != -1)
	{
		int newSize[2] = { width,height };
		CBufferManager::Instance()->getCBuffer(index)->updateCBuffer(newSize, sizeof(newSize));
	}

	//this->defaultRenderTarget.changeViewport({ 0,0,static_cast<float>(width),static_cast<float>(height),0,1 });
}

void Window::handleResize(GLFWwindow* window, int width, int height)
{
	static_cast<Window*>(glfwGetWindowUserPointer(window))->setSize(width, height);

}

void Window::bindRTV()
{
	//ID3D11RenderTargetView* renderTargetViews[1] = { renderTargetView.Get() };
	//device->getDeviceContext()->OMSetRenderTargets(1, renderTargetViews, depthStencilView.Get());

	defaultRenderTarget.bind();

	//D3D11_VIEWPORT port = { 0,0,width,height ,0,1 };

	//device->getDeviceContext()->RSSetViewports(1, &port);
} 