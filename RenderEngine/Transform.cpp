#include "Transform.h"

Transform::Transform(const SimpleMath::Vector3& position, const Quaternion_& rotation, const SimpleMath::Vector3& scale)
	: _position(position)
	, _rotation(rotation)
	, _originalPosition(position)
	, _originalRotation(rotation)
	, _scale(scale)
	//, Component(ComponentType::TRANSFORM, "Transform")
{}

Transform::~Transform() {}

Transform & Transform::operator=(const Transform & t)
{
	this->_position = t._position;
	this->_rotation = t._rotation;
	this->_scale = t._scale;
	return *this;
}

void Transform::Translate(const SimpleMath::Vector3& translation)
{
	_position = _position + translation;
}

void Transform::Translate(float x, float y, float z)
{
	_position = _position + SimpleMath::Vector3(x, y, z);
}

void Transform::Scale(const SimpleMath::Vector3& scl)
{
	_scale = scl;
}

void Transform::RotateAroundPointAndAxis(const SimpleMath::Vector3& axis, float angle, const SimpleMath::Vector3& point)
{
	SimpleMath::Vector3 R(_position - point);
	const Quaternion_ rot = Quaternion_::FromAxisAngle(axis, angle);
	R = rot.TransformVector(R);
	_position = point + R;
}

XMMATRIX Transform::WorldTransformationMatrix() const
{
	XMVECTOR scale = _scale;
	XMVECTOR translation = _position;

	//Quaternion_ Q = Quaternion_(GetRotationF3());
	Quaternion_ Q = _rotation;
	XMVECTOR rotation = XMVectorSet(Q.V.x, Q.V.y, Q.V.z, Q.S);
	//XMVECTOR rotOrigin = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR rotOrigin = XMVectorZero();
	return XMMatrixAffineTransformation(scale, rotOrigin, rotation, translation);
}

DirectX::XMMATRIX Transform::WorldTransformationMatrix_NoScale() const
{
	XMVECTOR scale = XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);
	XMVECTOR translation = _position;
	Quaternion_ Q = _rotation;
	XMVECTOR rotation = XMVectorSet(Q.V.x, Q.V.y, Q.V.z, Q.S);
	XMVECTOR rotOrigin = XMVectorZero();
	return XMMatrixAffineTransformation(scale, rotOrigin, rotation, translation);
}

XMMATRIX Transform::RotationMatrix() const
{
	return _rotation.Matrix();
}

// builds normal matrix from world matrix, ignoring translation
// and using inverse-transpose of rotation/scale matrix
DirectX::XMMATRIX Transform::NormalMatrix(const XMMATRIX& world)
{
	XMMATRIX nrm = world;
	nrm.r[3].m128_f32[0] = nrm.r[3].m128_f32[1] = nrm.r[3].m128_f32[2] = 0;
	nrm.r[3].m128_f32[3] = 1;
	XMVECTOR Det = XMMatrixDeterminant(nrm);
	nrm = XMMatrixInverse(&Det, nrm);
	nrm = XMMatrixTranspose(nrm);
	return nrm;
}
