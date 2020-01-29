#pragma once
#include <d3d11.h>
#include "DX11Render.h"
#include "Math/SimpleMath.h"

using namespace DirectX;

class ViewPort
{
public:
	ViewPort();
	~ViewPort();

	bool Initial(DX11Render* render, HWND hwd);

	void Resize(int w, int h);
	void ClearBackbuffer(SimpleMath::Color clr);

	void Present();
	
	ID3D11Device * GetDevice() { return m_d3dDevice; }
	ID3D11DeviceContext * GetContext() { return m_d3dDevContext; }

	void Release();
private:
	ID3D11Device *m_d3dDevice;
	ID3D11DeviceContext *m_d3dDevContext;

	IDXGISwapChain *m_swapChain;
	ID3D11Texture2D *m_depthStencilBuffer;
	ID3D11DepthStencilView *m_depthStencilView;
	ID3D11RenderTargetView *m_renderTargetView;
	//ID3D11RasterizerState *m_rasterizeState;

	D3D11_VIEWPORT m_viewport;

	DX11Render* m_render;
};

