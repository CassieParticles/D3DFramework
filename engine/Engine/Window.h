#pragma once

#include <string>
#include <d3d11.h>
#include <dxgi1_3.h>
#include <wrl.h>
#include <DirectXMath.h>

class GLFWwindow;

class Window
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	static Window* initializeWindow(const std::string& windowTitle, int windowWidth, int windowHeight);
	static Window* Instance();

	bool getWindowShouldClose();

	void clearBackBuffer(DirectX::XMFLOAT4 colour);
	void presentBackBuffer();

	void bindRTV();

protected:
	static Window* instance;

	Window(const std::string& windowTitle, int windowWidth, int windowHeight);
	~Window() = default;
	bool createWindow(const std::string& windowTitle, int windowWidth, int windowHeight);

	GLFWwindow* windowHandle;
	
	GLFWwindow* window;
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> deviceContext;
	ComPtr<IDXGIFactory2> factory;
	ComPtr<IDXGISwapChain1> swapChain;

	ComPtr<ID3D11DepthStencilState> depthStencilState;

	//TODO: Update this to use Render target when that is working
	ComPtr<ID3D11Texture2D> backBuffer;
	ComPtr<ID3D11Texture2D> depthBuffer;
	ComPtr<ID3D11RenderTargetView> renderTargetView;
	ComPtr<ID3D11DepthStencilView> depthStencilView;

	//Window size
	int width{};
	int height{};
	void setSize(int width, int height);
	static void handleResize(GLFWwindow* window, int width, int height);
};