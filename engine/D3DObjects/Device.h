#pragma once
#include <d3d11.h>
#include <dxgi1_3.h>
#include <wrl.h>

class Device
{
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	static Device* InitializeDevices();
	static Device* Instance() { return instance; }

	const ComPtr<ID3D11Device>& getDevice() { return device; }
	const ComPtr<ID3D11DeviceContext>& getDeviceContext() { return deviceContext; }

protected:
	Device();
	~Device() = default;

	static Device* instance;

	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> deviceContext;
};