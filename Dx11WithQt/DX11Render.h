#pragma once
#include <QWidget>
#include <d3d11.h>
// #include <d3dx11.h>
// #include <d3dx10.h>
// #include <xnamath.h>
#include <functional>
#include <assert.h>
#include <memory.h>

#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>
class DX11Render
{
public:
	DX11Render();
	~DX11Render();

	bool InitialDevice();

	ID3D11Device* getDevice(){ return m_pD3dDevice; }
	ID3D11DeviceContext* getDeviceContex(){ return m_pDeviceContext; }
	UINT	getQualityLevel(){ return m_qualityLevel; }
private:
	ID3D11Device* m_pD3dDevice;
	ID3D11DeviceContext* m_pDeviceContext;
	UINT	m_qualityLevel;

};

