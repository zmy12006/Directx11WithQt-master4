#pragma once

#include <QWidget>

//����D3D��ص�ͷ�ļ�
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

#define SafeRelease(X) {X->Release(); X=nullptr;}
#define SAFE_RELEASE(p) {if(p){(p)->Release(); p=0;}}

using namespace DirectX;

//����ṹ
struct Vertex
{
	Vertex(){}
	Vertex(float x, float y, float z,
		float cr, float cg, float cb, float ca)
		: pos(x, y, z), color(cr, cg, cb, ca){}

	XMFLOAT3 pos;
	XMFLOAT4 color;
};
//����layout (�Ӹ�const���ܱ��������֪��Ϊʲô)
const D3D11_INPUT_ELEMENT_DESC in_layout[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};
const UINT numElements = ARRAYSIZE(in_layout);
//����shader��constant buffer
struct VS_ConstantBuffer
{
	XMMATRIX WVP;
};

