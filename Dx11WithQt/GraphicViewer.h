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
	//重写虚函数
	virtual void resizeEvent(QResizeEvent *event); //当窗口尺寸改变时响应
	virtual void paintEvent(QPaintEvent *event);   //窗口绘制函数，用于render三维场景
	//键盘和鼠标监听
	virtual void keyPressEvent(QKeyEvent *event);
	virtual void keyReleaseEvent(QKeyEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void wheelEvent(QWheelEvent *event);

private:
	void ResizeD3D();   //重置D3D
	void InitScene();   //初始化场景
	void UpdateScene(double deltaTime); //更新场景
	void RenderScene(); //渲染场景
	void CleanUp();     //释放资源

private:
	DX11Render* mScene;

	ViewPort	mViewPort;

private:
	//D3D相关的变量
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
	bool isWireFrame; //是否线框渲染模式



	//Xxnamath数学库里面的变量只能写成全局的，不要写为类成员
	//二个cube的世界矩阵
	XMMATRIX cube1WorldMat;
	XMMATRIX cube2WorldMat;
	//物体的变换矩阵
	XMMATRIX rotation;     //选中矩阵
	XMMATRIX scale;        //缩放矩阵
	XMMATRIX translation;  //平移矩阵
	float rotAngle = 0.1f; //旋转角
	float rotateSpeed = 1.0f; //旋转速度
	//摄像机参数
	XMMATRIX camView;
	XMMATRIX camProjection;

	XMVECTOR camPosition;
	XMVECTOR camTarget;
	XMVECTOR camUp;

	//fps相关的全局变量
	double countsPerSecond = 0.0;
	__int64 CounterStart = 0;

	int frameCount = 0;
	int fps = 0;

	__int64 frameTimeOld = 0;
	double frameTime;

	//fps相关函数
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

	//获取每帧间隔时间
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

