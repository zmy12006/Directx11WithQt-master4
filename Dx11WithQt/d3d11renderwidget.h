/*
//D3D��Ⱦ��Widget
//û�мӸ��ְ�ȫ������䣬Ϊ�˴���ļ��
*/

#ifndef D3D11RENDERWIDGET_H
#define D3D11RENDERWIDGET_H

#include <QWidget>

//����D3D��ص�ͷ�ļ�
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
	//D3D��صı���
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
	void InitD3D();     //��ʼ��D3D11
	void ResizeD3D();   //����D3D
	void InitScene();   //��ʼ������
	void UpdateScene(double deltaTime); //���³���
	void RenderScene(); //��Ⱦ����
	void CleanUp();     //�ͷ���Դ

private:
	bool isWireFrame; //�Ƿ��߿���Ⱦģʽ
};

#endif // D3D11RENDERWIDGET_H
