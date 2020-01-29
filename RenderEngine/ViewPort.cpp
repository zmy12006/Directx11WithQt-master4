#include "Common.h"
#include "ViewPort.h"

ViewPort::ViewPort():
m_d3dDevice(0),
m_d3dDevContext(0),
m_swapChain(0),
m_depthStencilBuffer(0),
m_depthStencilView(0),
m_renderTargetView(0),
m_render(0)
{

}

ViewPort::~ViewPort()
{
	Release();
}

bool ViewPort::Initial(DX11Render* render, HWND hwd)
{
	m_render = render;

	m_d3dDevice = m_render->getDevice();
	m_d3dDevContext = m_render->getDeviceContex();

	HRESULT	hr;
	DXGI_SWAP_CHAIN_DESC scDesc = { 0 };
	scDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	//scDesc.BufferDesc.Width = iWindowsWidth;
	//scDesc.BufferDesc.Height = iWindowHeight;
	scDesc.BufferDesc.RefreshRate.Numerator = 60;
	scDesc.BufferDesc.RefreshRate.Denominator = 1;
	scDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scDesc.BufferCount = 1;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.Flags = 0;
	scDesc.OutputWindow = (HWND)hwd/*winId()*/;
	scDesc.SampleDesc.Count = m_render->getQualityLevel() <= 1 ? 1 : 4;
	scDesc.SampleDesc.Quality = m_render->getQualityLevel() <= 1 ? 0 : m_render->getQualityLevel() - 1;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scDesc.Windowed = true;

	IDXGIDevice *pDxgiDevice(NULL);
	hr = m_render->getDevice()->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&pDxgiDevice));
	if (FAILED(hr))
	{
		//qDebug() << "Get DXGIDevice failed!";
		return false;
	}
	IDXGIAdapter *pDxgiAdapter(NULL);
	hr = pDxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&pDxgiAdapter));
	if (FAILED(hr))
	{
		//qDebug() << "Get DXGIAdapter failed!";
		return false;
	}
	IDXGIFactory *pDxgiFactory(NULL);
	hr = pDxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pDxgiFactory));
	if (FAILED(hr))
	{
		//qDebug() << "Get DXGIFactory failed!";
		return false;
	}
	hr = pDxgiFactory->CreateSwapChain(m_render->getDevice(), &scDesc, &m_swapChain);
	if (FAILED(hr))
	{
		//qDebug() << "Create swap chain failed!";
		return false;
	}
	SafeRelease(pDxgiFactory);
	SafeRelease(pDxgiAdapter);
	SafeRelease(pDxgiDevice);

	return true;
}

void ViewPort::Resize(int w, int h)
{
	//当窗口尺寸变化时，必须重新设置帧缓存、深度缓存、模板缓存、视口

	SAFE_RELEASE(m_renderTargetView);
	SAFE_RELEASE(m_depthStencilView);
	SAFE_RELEASE(m_depthStencilBuffer);

	HRESULT hr;
	m_swapChain->ResizeBuffers(1, w, h, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
	//Create our BackBuffer
	ID3D11Texture2D* backBuffer;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

	//Create our Render Target
	hr = m_d3dDevice->CreateRenderTargetView(backBuffer, NULL, &m_renderTargetView);
	SAFE_RELEASE(backBuffer);

	//Describe our Depth/Stencil Buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = w;
	depthStencilDesc.Height = h;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	//Create the Depth/Stencil View
	m_d3dDevice->CreateTexture2D(&depthStencilDesc, NULL, &m_depthStencilBuffer);
	m_d3dDevice->CreateDepthStencilView(m_depthStencilBuffer, NULL, &m_depthStencilView);

	//Set our Render Target
	m_d3dDevContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

	//Create the Viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = w;
	viewport.Height = h;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	m_viewport = viewport;
	//Set the Viewport
	m_d3dDevContext->RSSetViewports(1, &viewport);
}

void ViewPort::ClearBackbuffer(SimpleMath::Color clr)
{
	m_d3dDevContext->RSSetViewports(1, &m_viewport);
	m_d3dDevContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

	//Clear our backbuffer
	float bgColor[4] = { (0.0f, 0.0f, 0.0f, 0.0f) };
	m_d3dDevContext->ClearRenderTargetView(m_renderTargetView, bgColor);

	//Refresh the Depth/Stencil view
	m_d3dDevContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void ViewPort::Present()
{
	m_swapChain->Present(0, 0);
}

void ViewPort::Release()
{
	SAFE_RELEASE(m_swapChain);
	SAFE_RELEASE(m_depthStencilBuffer);
	SAFE_RELEASE(m_depthStencilView);
	SAFE_RELEASE(m_renderTargetView);
}