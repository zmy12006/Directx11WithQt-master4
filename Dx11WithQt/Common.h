#pragma once

#include <QWidget>

//包含D3D相关的头文件
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

//顶点结构
struct Vertex
{
	Vertex(){}
	Vertex(float x, float y, float z,
		float cr, float cg, float cb, float ca)
		: pos(x, y, z), color(cr, cg, cb, ca){}

	XMFLOAT3 pos;
	XMFLOAT4 color;
};
//顶点layout (加个const才能编译过，不知道为什么)
const D3D11_INPUT_ELEMENT_DESC in_layout[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};
const UINT numElements = ARRAYSIZE(in_layout);
//传到shader的constant buffer
struct VS_ConstantBuffer
{
	XMMATRIX WVP;
};

