#include <string>
#include "Common.h"
#include "DX11Render.h"


DX11Render::DX11Render()
{
	m_qualityLevel = 0;
}


DX11Render::~DX11Render()
{
	SAFE_RELEASE(m_pD3dDevice);
	SAFE_RELEASE(m_pDeviceContext);
}

bool DX11Render::InitialDevice()
{
	HRESULT	hr;

	D3D_FEATURE_LEVEL featureLevels[6] = { D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(_DEBUG)
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL	curLevel;
	hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, creationFlags, featureLevels, 6, D3D11_SDK_VERSION,
		&m_pD3dDevice, &curLevel, &m_pDeviceContext);
	if (FAILED(hr))
	{
		//qDebug() << QStringLiteral("Craete device failed!");
		return false;
	}

	if (curLevel != D3D_FEATURE_LEVEL_11_0)
	{
		//qDebug() << QStringLiteral("您的机器不支持D3D11特性，程序可能无法正确显示效果");
	}

	m_pD3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_B8G8R8A8_UNORM, 4, &m_qualityLevel);


#if defined(DEBUG) || defined(_DEBUG)
	std::string level(("Unkown"));
	switch (curLevel)
	{
	case D3D_FEATURE_LEVEL_11_0:
		level = "11_0";
		break;
	case D3D_FEATURE_LEVEL_10_1:
		level = "10_1";
		break;
	case D3D_FEATURE_LEVEL_10_0:
		level = "10_0";
		break;
	case D3D_FEATURE_LEVEL_9_3:
		level = "9_3";
		break;
	case D3D_FEATURE_LEVEL_9_2:
		level = "9_2";
		break;
	case D3D_FEATURE_LEVEL_9_1:
		level = "9_1";
		break;
	}
#endif
	return true;
}