#include "Device.h"

#include <iostream>

Device* Device::instance = nullptr;

Device* Device::InitializeDevices()
{
	if (!instance)
	{
		instance = new Device();
	}

	return instance;
}

Device::Device()
{
	//TODO: Add flags so this is not debug mode when compiled on release
#ifdef DEBUG
	constexpr D3D11_CREATE_DEVICE_FLAG debugFlag = D3D11_CREATE_DEVICE_DEBUG;
	std::cout << "Debug\n";
#else 
	constexpr D3D11_CREATE_DEVICE_FLAG debugFlag = (D3D11_CREATE_DEVICE_FLAG)0;
	
#endif

	//Set up the D3D device and device context
	constexpr D3D_FEATURE_LEVEL deviceFeatureLevel = D3D_FEATURE_LEVEL_11_0;

	HRESULT errorCode = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, debugFlag, &deviceFeatureLevel, 1, D3D11_SDK_VERSION, &device, nullptr, &deviceContext);
	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create device/device context\n";
		return;
	}
}
