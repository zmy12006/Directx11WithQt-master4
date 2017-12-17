/*
//D3D渲染的Widget
//没有加各种安全检测的语句，为了代码的简洁
*/

#ifndef D3D11RENDERWIDGET_H
#define D3D11RENDERWIDGET_H

#include <QWidget>

//包含D3D相关的头文件
#include <d3d11.h>
//#include <d3dx11.h>
//#include <d3dx10.h>
//#include <xnamath.h>	

#include <functional>
#include <assert.h>
#include <memory.h>

#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>

#include "Common.h"

class D3d11RenderWidget : public QWidget
{
	Q_OBJECT

public:
	D3d11RenderWidget(QWidget *parent);
	~D3d11RenderWidget();
	virtual QPaintEngine *paintEngine() const
	{
		return NULL;
	}

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
	//D3D相关的变量
	ID3D11Device *m_d3dDevice;
	ID3D11DeviceContext *m_d3dDevContext;
	IDXGISwapChain *m_swapChain;
	ID3D11Texture2D *m_depthStencilBuffer;
	ID3D11DepthStencilView *m_depthStencilView;
	ID3D11RenderTargetView *m_renderTargetView;
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

private:
	void InitD3D();     //初始化D3D11
	void ResizeD3D();   //重置D3D
	void InitScene();   //初始化场景
	void UpdateScene(double deltaTime); //更新场景
	void RenderScene(); //渲染场景
	void CleanUp();     //释放资源

private:
	bool isWireFrame; //是否线框渲染模式
};

#endif // D3D11RENDERWIDGET_H
