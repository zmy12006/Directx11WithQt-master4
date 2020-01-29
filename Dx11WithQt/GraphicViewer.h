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

#include "ViewPort.h"
#include "Common.h"

class DX11Render;
class GraphicViewer : public QWidget
{
	Q_OBJECT
public:
	GraphicViewer(QWidget* parent);
	~GraphicViewer();

	virtual QPaintEngine *paintEngine() const
	{
		return NULL;
	}

	bool Initial(DX11Render* s);

private:
	//��д�麯��
	virtual void resizeEvent(QResizeEvent *event); //�����ڳߴ�ı�ʱ��Ӧ
	virtual void paintEvent(QPaintEvent *event);   //���ڻ��ƺ���������render��ά����
	//���̺�������
	virtual void keyPressEvent(QKeyEvent *event);
	virtual void keyReleaseEvent(QKeyEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void wheelEvent(QWheelEvent *event);

private:
	void ResizeD3D();   //����D3D
	void InitScene();   //��ʼ������
	void UpdateScene(double deltaTime); //���³���
	void RenderScene(); //��Ⱦ����
	void CleanUp();     //�ͷ���Դ

private:
	DX11Render* mScene;

	ViewPort	mViewPort;

private:
	//D3D��صı���
	ID3D11Device *m_d3dDevice;
	ID3D11DeviceContext *m_d3dDevContext;
	//IDXGISwapChain *m_swapChain;
	//ID3D11Texture2D *m_depthStencilBuffer;
	//ID3D11DepthStencilView *m_depthStencilView;
	//ID3D11RenderTargetView *m_renderTargetView;
	ID3D11RasterizerState *m_rasterizeState;

	ID3D11Buffer *m_squareVertexBuffer;
	ID3D11Buffer *m_squareIndiceBuffer;
	ID3D11VertexShader *m_VS;
	ID3D11PixelShader *m_PS;
	ID3D10Blob *m_VS_buffer;
	ID3D10Blob *m_PS_buffer;
	ID3D11InputLayout *m_inputLayout;
	ID3D11Buffer *m_VS_objectBuffer;


	VS_ConstantBuffer m_VS_ConstantBuffer;

	D3D11_VIEWPORT m_viewport;
private:
	bool isWireFrame; //�Ƿ��߿���Ⱦģʽ



	//Xxnamath��ѧ������ı���ֻ��д��ȫ�ֵģ���ҪдΪ���Ա
	//����cube���������
	XMMATRIX cube1WorldMat;
	XMMATRIX cube2WorldMat;
	//����ı任����
	XMMATRIX rotation;     //ѡ�о���
	XMMATRIX scale;        //���ž���
	XMMATRIX translation;  //ƽ�ƾ���
	float rotAngle = 0.1f; //��ת��
	float rotateSpeed = 1.0f; //��ת�ٶ�
	//���������
	XMMATRIX camView;
	XMMATRIX camProjection;

	XMVECTOR camPosition;
	XMVECTOR camTarget;
	XMVECTOR camUp;

	//fps��ص�ȫ�ֱ���
	double countsPerSecond = 0.0;
	__int64 CounterStart = 0;

	int frameCount = 0;
	int fps = 0;

	__int64 frameTimeOld = 0;
	double frameTime;

	//fps��غ���
	void startFPStimer()
	{
		LARGE_INTEGER frequencyCount;
		QueryPerformanceFrequency(&frequencyCount);

		countsPerSecond = double(frequencyCount.QuadPart);

		QueryPerformanceCounter(&frequencyCount);
		CounterStart = frequencyCount.QuadPart;
	}

	double getTime()
	{
		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);
		return double(currentTime.QuadPart - CounterStart) / countsPerSecond;
	}

	//��ȡÿ֡���ʱ��
	double getFrameTime()
	{
		LARGE_INTEGER currentTime;
		__int64 tickCount;
		QueryPerformanceCounter(&currentTime);

		tickCount = currentTime.QuadPart - frameTimeOld;
		frameTimeOld = currentTime.QuadPart;

		if (tickCount < 0.0f)
			tickCount = 0.0f;

		return float(tickCount) / countsPerSecond;
	}

};

