#pragma once
#include <d3d11.h>
#include <dxgi1_3.h>
#include <wrl.h>

class D3DDevice
{
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	static D3DDevice* InitializeDevices();
	static D3DDevice* Instance() { return instance; }

	const ComPtr<ID3D11Device>& getDevice() { return device; }
	const ComPtr<ID3D11DeviceContext>& getDeviceContext() { return deviceContext; }

protected:
	D3DDevice();
	~D3DDevice() = default;

	static D3DDevice* instance;

	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> deviceContext;
};