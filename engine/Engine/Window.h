#pragma once

#include <string>
#include <d3d11.h>
#include <dxgi1_3.h>
#include <wrl.h>
#include <DirectXMath.h>

#include <engine/D3DObjects/RenderTarget.h>

class GLFWwindow;
class Device;

class Window
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	static Window* InitializeWindow(const std::string& windowTitle, int windowWidth, int windowHeight);
	static Window* Instance();

	bool getWindowShouldClose();

	const ComPtr<IDXGIFactory2>& getFactory() { return factory; }
	const ComPtr<IDXGISwapChain1>& getSwapChain() { return swapChain; }
	const ComPtr<ID3D11Texture2D> getBackBuffer() { return backBuffer; }
	const ComPtr<ID3D11Texture2D> getDepthBuffer() { return depthBuffer; }

	GLFWwindow* getWindow() { return window; }

	void changeBackBufferClearColour(DirectX::XMFLOAT4 newColour);
	void clearBackBuffer();
	void presentBackBuffer();

	void bindRTV();

	int getWidth() { return width; }
	int getHeight() { return height; }

protected:
	static Window* instance;

	Window(const std::string& windowTitle, int windowWidth, int windowHeight);
	~Window() = default;
	bool createWindow(const std::string& windowTitle, int windowWidth, int windowHeight);
	
	GLFWwindow* window;

	Device* device;

	ComPtr<IDXGIFactory2> factory;
	ComPtr<IDXGISwapChain1> swapChain;

	ComPtr<ID3D11DepthStencilState> depthStencilState;

	//TODO: Update this to use Render target when that is working
	ComPtr<ID3D11Texture2D> backBuffer;
	ComPtr<ID3D11Texture2D> depthBuffer;
	ComPtr<ID3D11RenderTargetView> renderTargetView;
	ComPtr<ID3D11DepthStencilView> depthStencilView;

	RenderTarget defaultRenderTarget;

	//Window size
	int width{};
	int height{};
	void setSize(int width, int height);
	static void handleResize(GLFWwindow* window, int width, int height);
};