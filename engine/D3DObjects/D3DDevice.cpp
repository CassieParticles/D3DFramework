#include "D3DDevice.h"

#include <iostream>

D3DDevice* D3DDevice::instance = nullptr;

D3DDevice* D3DDevice::InitializeDevices()
{
	if (!instance)
	{
		instance = new D3DDevice();
	}

	return instance;
}

D3DDevice::D3DDevice()
{
	//TODO: Add flags so this is not debug mode when compiled on release
	constexpr D3D11_CREATE_DEVICE_FLAG debugFlag = D3D11_CREATE_DEVICE_DEBUG;

	//Set up the D3D device and device context
	constexpr D3D_FEATURE_LEVEL deviceFeatureLevel = D3D_FEATURE_LEVEL_11_0;

	HRESULT errorCode = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, debugFlag, &deviceFeatureLevel, 1, D3D11_SDK_VERSION, &device, nullptr, &deviceContext);
	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create device/device context\n";
		return;
	}
}
