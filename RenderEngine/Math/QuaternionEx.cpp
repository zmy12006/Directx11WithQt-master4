
#include "QuaternionEx.h"

#define CLAMP(x , min , max) ((x) > (max) ? (max) : ((x) < (min) ? (min) : x))

// void QuaternionEx::set(const Vector3& axis, float angle)
// {
// 	createFromAxisAngle(axis, angle, this);
// }
// 
// void QuaternionEx::set(Matrix& m)
// {
// 	createFromRotationMatrix(m, this);
// }
// 
// void QuaternionEx::set(const Vector3& angle)
// {
// 	float cx = cos(angle.x / 2);
// 	float sx = sin(angle.x / 2);
// 	float cy = cos(angle.y / 2);
// 	float sy = sin(angle.y / 2);
// 	float cz = cos(angle.z / 2);
// 	float sz = sin(angle.z / 2);
// 
// 	this->w = cx*cy*cz + sx*sy*sz;
// 	this->x = sx*cy*cz - cx*sy*sz;
// 	this->y = cx*sy*cz + sx*cy*sz;
// 	this->z = cx*cy*sz - sx*sy*cz;
// }
// 
// Vector3 QuaternionEx::GetEulerAngle()
// {
// 	Vector3 ret;
// 
// 	float test = y*z + x*w;
// 	if (test > 0.4999f)
// 	{
// 		ret.z = 2.0f * atan2(y, w);
// 		ret.y = 3.1415926f / 2.0f;// PIOver2;
// 		ret.x = 0.0f;
// 		return ret;
// 	}
// 	if (test < -0.4999f)
// 	{
// 		ret.z = 2.0f * atan2(y, w);
// 		ret.y = -3.1415926f / 2.0f;// PIOver2;
// 		ret.x = 0.0f;
// 		return ret;
// 	}
// 	float sqx = x * x;
// 	float sqy = y * y;
// 	float sqz = z * z;
// 	ret.z = atan2(2.0f * z * w - 2.0f * y * x, 1.0f - 2.0f * sqz - 2.0f * sqx);
// 	ret.y = asin(2.0f * test);
// 	ret.x = atan2(2.0f * y * w - 2.0f * z * x, 1.0f - 2.0f * sqy - 2.0f * sqx);
// 
// 	return ret;
// }
// 
// void QuaternionEx::createFromAxisAngle(const Vector3& axis, float angle, Quaternion* dst)
// {
// 	float halfAngle = angle * 0.5f;
// 	float sinHalfAngle = sinf(halfAngle);
// 
// 	Vector3 normal(axis);
// 	normal.Normalize();
// 	dst->x = normal.x * sinHalfAngle;
// 	dst->y = normal.y * sinHalfAngle;
// 	dst->z = normal.z * sinHalfAngle;
// 	dst->w = cosf(halfAngle);
// }
// 
// void QuaternionEx::createFromRotationMatrix( Matrix& m, Quaternion* dst)
// {
// 	//m.getRotation(dst);
// 	Vector3 s;
// 	Vector3 t;
// 	m.Decompose(s, *dst, t);
// }

Quaternion QuaternionEx::CreateFromAxisAngle(const Vector3& axis, float angle)
{
	using namespace DirectX;
	XMVECTOR a = XMLoadFloat3(&axis);

	Quaternion R;
	XMStoreFloat4(&R, XMQuaternionRotationAxis(a, angle));
	return R;
}

Quaternion QuaternionEx::CreateFromYawPitchRoll(float yaw, float pitch, float roll)
{
	using namespace DirectX;
	Quaternion R;
	XMStoreFloat4(&R, XMQuaternionRotationRollPitchYaw(pitch, yaw, roll));
	return R;
}

Quaternion QuaternionEx::CreateFromRotationMatrix(const Matrix& M)
{
	using namespace DirectX;
	XMMATRIX M0 = XMLoadFloat4x4(&M);

	Quaternion R;
	XMStoreFloat4(&R, XMQuaternionRotationMatrix(M0));
	return R;
}

void QuaternionEx::GetAxisAngle(const Quaternion& q, Vector3& axis, float& angle)
{
	using namespace DirectX;
	XMVECTOR vecQ = XMLoadFloat4(&q);
	XMVECTOR vecAxis;
	XMQuaternionToAxisAngle(&vecAxis, &angle, vecQ);
	XMStoreFloat3(&axis, vecAxis);
}

Quaternion QuaternionEx::SetEulerAngle(float yaw, float pitch, float roll)
{
	float fCosHRoll = cos(roll * .5f);//x
	float fSinHRoll = sin(roll * .5f);
	float fCosHPitch = cos(pitch * .5f);//y
	float fSinHPitch = sin(pitch * .5f);
	float fCosHYaw = cos(yaw * .5f);//z
	float fSinHYaw = sin(yaw * .5f);

	/// Cartesian coordinate System
	//w = fCosHRoll * fCosHPitch * fCosHYaw + fSinHRoll * fSinHPitch * fSinHYaw;
	//x = fSinHRoll * fCosHPitch * fCosHYaw - fCosHRoll * fSinHPitch * fSinHYaw;
	//y = fCosHRoll * fSinHPitch * fCosHYaw + fSinHRoll * fCosHPitch * fSinHYaw;
	//z = fCosHRoll * fCosHPitch * fSinHYaw - fSinHRoll * fSinHPitch * fCosHYaw;
	QuaternionEx q;
	q.w = fCosHRoll * fCosHPitch * fCosHYaw + fSinHRoll * fSinHPitch * fSinHYaw;
	q.x = fCosHRoll * fSinHPitch * fCosHYaw + fSinHRoll * fCosHPitch * fSinHYaw;
	q.y = fCosHRoll * fCosHPitch * fSinHYaw - fSinHRoll * fSinHPitch * fCosHYaw;
	q.z = fSinHRoll * fCosHPitch * fCosHYaw - fCosHRoll * fSinHPitch * fSinHYaw;

	return q;
}

Vector3 QuaternionEx::GetEulerAngle(Quaternion q)
{
	Vector3 v;

	/// Cartesian coordinate System 
	//ea.m_fRoll  = atan2(2 * (w * x + y * z) , 1 - 2 * (x * x + y * y));
	//ea.m_fPitch = asin(2 * (w * y - z * x));
	//ea.m_fYaw   = atan2(2 * (w * z + x * y) , 1 - 2 * (y * y + z * z));

	/*ea.m_fRoll*/ v.z = atan2(2 * (q.w * q.z + q.x * q.y), 1 - 2 * (q.z * q.z + q.x * q.x));
	/*ea.m_fPitch*/v.x = asin(CLAMP(2 * (q.w * q.x - q.y * q.z), -1.0f, 1.0f));
	/*ea.m_fYaw*/v.y = atan2(2 * (q.w * q.y + q.z * q.x), 1 - 2 * (q.x * q.x + q.y * q.y));

	return v;
}


#include <cmath>
#include <algorithm>	// min, max

Quaternion_::Quaternion_(float s, const Vector3& v)
	:
	S(s),
	V(v)
{}

Quaternion_::Quaternion_() : S(0), V() {}

// Pitch:	X
// Yaw:		Y
// Roll:	Z
//Quaternion::Quaternion(float pitch, float yaw, float roll)
//{
//	// source: https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
//	float t0 = std::cosf(yaw * 0.5f);
//	float t1 = std::sinf(yaw * 0.5f);
//	float t2 = std::cosf(roll * 0.5f);
//	float t3 = std::sinf(roll * 0.5f);
//	float t4 = std::cosf(pitch * 0.5f);
//	float t5 = std::sinf(pitch * 0.5f);
//
//	float w = t0 * t2 * t4 + t1 * t3 * t5;
//	float x = t0 * t3 * t4 - t1 * t2 * t5;
//	float y = t0 * t2 * t5 + t1 * t3 * t4;
//	float z = t1 * t2 * t4 - t0 * t3 * t5;
//
//	S = w;
//	//V = vec3(y, x, z);
//	V = vec3(y, z, x);	// i need an explanation why this works and not others:( 
//							// read: euler vs yawpitchroll
//	//V = vec3(z, x, y);
//}

//Quaternion::Quaternion(const vec3& pitchYawRoll)
//	:
//	Quaternion(pitchYawRoll.x, pitchYawRoll.y, pitchYawRoll.z)
//{}

Quaternion_::Quaternion_(const XMMATRIX& rotMatrix)
{
	//const XMMATRIX & m = rotMatrix;
	//S = 0.5f * sqrt(m.r[0].m128_f32[0] + m.r[1].m128_f32[1] + m.r[2].m128_f32[2] + 1);
	//V.x = (m.r[2].m128_f32[1] - m.r[1].m128_f32[2]) / (4.0f * S);
	//V.y = (m.r[0].m128_f32[2] - m.r[2].m128_f32[0]) / (4.0f * S);
	//V.z = (m.r[1].m128_f32[0] - m.r[0].m128_f32[1]) / (4.0f * S);

	// Therefore, I decided to use decompose function to get the XM quaternion, which doesn't work
	// with my system as well. I have to rotate it 180degrees on Y to get the correct rotation
	XMVECTOR scl = XMVectorZero();
	XMVECTOR quat = XMVectorZero();
	XMVECTOR trans = XMVectorZero();
	XMMatrixDecompose(&scl, &quat, &trans, XMMatrixTranspose(rotMatrix));
	//XMMatrixDecompose(&scl, &quat, &trans, rotMatrix);

	// hack zone
	//quat.m128_f32[2] *= -1.0f;

	//*this = Quaternion(quat.m128_f32[3], quat); //*Quaternion(0.0f, XM_PI, 0.0f);
	*this = Quaternion_(quat.m128_f32[3], quat).Conjugate(); //*Quaternion(0.0f, XM_PI, 0.0f);
	int a = 5;
}

Quaternion_::Quaternion_(float s, const XMVECTOR & v)
	:
	S(s),
	V(v.m128_f32[0], v.m128_f32[1], v.m128_f32[2])
{}

Quaternion_ Quaternion_::Identity()
{
	return Quaternion_(1, Vector3(0.0f, 0.0f, 0.0f));
}


Quaternion_ Quaternion_::FromAxisAngle(const XMVECTOR& axis, const float angle)
{
	const float half_angle = angle / 2;
	Quaternion_ Q = Quaternion_::Identity();
	Q.S = cosf(half_angle);
	Q.V = axis * sinf(half_angle);
	return Q;
}

Quaternion_ Quaternion_::Lerp(const Quaternion_ & from, const Quaternion_ & to, float t)
{
	return  from * (1.0f - t) + to * t;
}

Quaternion_ Quaternion_::Slerp(const Quaternion_ & from, const Quaternion_ & to, float t)
{
	double alpha = std::acos(from.Dot(to));
	if (alpha < 0.00001) return from;
	double sina = std::sin(alpha);
	double sinta = std::sin(t * alpha);
	Quaternion_ interpolated = from * static_cast<float>(std::sin(alpha - t * alpha) / sina) +
		to * static_cast<float>(sinta / sina);
	interpolated.Normalize();
	return interpolated;
}

Vector3 Quaternion_::ToEulerRad(const Quaternion_& Q)
{
	// source: https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
	double ysqr = Q.V.y * Q.V.y;
	double t0 = -2.0f * (ysqr + Q.V.z * Q.V.z) + 1.0f;
	double t1 = +2.0f * (Q.V.x * Q.V.y - Q.S * Q.V.z);
	double t2 = -2.0f * (Q.V.x * Q.V.z + Q.S * Q.V.y);
	double t3 = +2.0f * (Q.V.y * Q.V.z - Q.S * Q.V.x);
	double t4 = -2.0f * (Q.V.x * Q.V.x + ysqr) + 1.0f;

	t2 = t2 > 1.0f ? 1.0f : t2;
	t2 = t2 < -1.0f ? -1.0f : t2;

	float pitch = static_cast<float>(std::asin(t2));
	float roll = static_cast<float>(std::atan2(t3, t4));
	float yaw = static_cast<float>(std::atan2(t1, t0));
	return Vector3(roll, pitch, yaw);	// ??? (probably due to wiki convention)
}

Vector3 Quaternion_::ToEulerDeg(const Quaternion_& Q)
{
	Vector3 eul = Quaternion_::ToEulerRad(Q);
	eul.x *= RAD2DEG;
	eul.y *= RAD2DEG;
	eul.z *= RAD2DEG;
	return eul;
}


Quaternion_ Quaternion_::operator+(const Quaternion_ & q) const
{
	Quaternion_ result;
	XMVECTOR V1 = XMVectorSet(V.x, V.y, V.z, 0);
	XMVECTOR V2 = XMVectorSet(q.V.x, q.V.y, q.V.z, 0);

	result.S = this->S + q.S;
	result.V = V1 + V2;
	return result;
}

Quaternion_ Quaternion_::operator*(const Quaternion_ & q) const
{
	Quaternion_ result;
	XMVECTOR V1 = XMVectorSet(V.x, V.y, V.z, 0);
	XMVECTOR V2 = XMVectorSet(q.V.x, q.V.y, q.V.z, 0);

	// s1s2 - v1.v2 
	result.S = this->S * q.S - XMVector3Dot(V1, V2).m128_f32[0];
	// s1v2 + s2v1 + v1xv2
	result.V = this->S * V2 + q.S * V1 + XMVector3Cross(V1, V2);
	return result;
}

Quaternion_ Quaternion_::operator*(float c) const
{
	Quaternion_ result;
	result.S = c * S;
	result.V = Vector3(V.x*c, V.y*c, V.z*c);
	return result;
}


bool Quaternion_::operator==(const Quaternion_& q) const
{
	double epsilons[4] = { 99999.0, 99999.0, 99999.0, 99999.0 };
	epsilons[0] = static_cast<double>(q.V.x) - static_cast<double>(this->V.x);
	epsilons[1] = static_cast<double>(q.V.y) - static_cast<double>(this->V.y);
	epsilons[2] = static_cast<double>(q.V.z) - static_cast<double>(this->V.z);
	epsilons[3] = static_cast<double>(q.S) - static_cast<double>(this->S);
	bool same_x = std::abs(epsilons[0]) < 0.000001;
	bool same_y = std::abs(epsilons[1]) < 0.000001;
	bool same_z = std::abs(epsilons[2]) < 0.000001;
	bool same_w = std::abs(epsilons[3]) < 0.000001;
	return same_x && same_y && same_z && same_w;
}

// other operations
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif
float Quaternion_::Dot(const Quaternion_ & q) const
{
	XMVECTOR V1 = XMVectorSet(V.x, V.y, V.z, 0);
	XMVECTOR V2 = XMVectorSet(q.V.x, q.V.y, q.V.z, 0);
	return std::max(-1.0f, std::min(S*q.S + XMVector3Dot(V1, V2).m128_f32[0], 1.0f));
}

float Quaternion_::Len() const
{
	return sqrt(S*S + V.x*V.x + V.y*V.y + V.z*V.z);
}

Quaternion_ Quaternion_::Inverse() const
{
	Quaternion_ result;
	float f = 1.0f / (S*S + V.x*V.x + V.y*V.y + V.z*V.z);
	result.S = f * S;
	result.V = Vector3(-V.x*f, -V.y*f, -V.z*f);
	return result;
}

Quaternion_ Quaternion_::Conjugate() const
{
	Quaternion_ result;
	result.S = S;
	result.V = Vector3(-V.x, -V.y, -V.z);
	return result;
}

XMMATRIX Quaternion_::Matrix() const
{
	XMMATRIX m = XMMatrixIdentity();
	float y2 = V.y * V.y;
	float z2 = V.z * V.z;
	float x2 = V.x * V.x;
	float xy = V.x * V.y;
	float sz = S * V.z;
	float xz = V.x * V.z;
	float sy = S * V.y;
	float yz = V.y * V.z;
	float sx = S * V.x;

	// -Z X -Y
	// LHS
	XMVECTOR r0 = XMVectorSet(1.0f - 2.0f * (y2 + z2), 2 * (xy - sz), 2 * (xz + sy), 0);
	XMVECTOR r1 = XMVectorSet(2 * (xy + sz), 1.0f - 2.0f * (x2 + z2), 2 * (yz - sx), 0);
	XMVECTOR r2 = XMVectorSet(2 * (xz - sy), 2 * (yz + sx), 1.0f - 2.0f * (x2 + y2), 0);
	XMVECTOR r3 = XMVectorSet(0, 0, 0, 1);

	//XMVECTOR r0 = XMVectorSet(2 * (xy - sz), -2.0f * (xz + sy), -(1.0f - 2.0f * (y2 + z2)), 0);
	//XMVECTOR r1 = XMVectorSet(-(1.0f - 2.0f * (x2 + z2)), 2.0f * (yz - sx), -2.0f * (xy + sz), 0);
	//XMVECTOR r2 = XMVectorSet(-2 * (yz + sx), -(1.0f - 2.0f * (x2 + y2)), 2.0f * (xz - sy), 0);
	//XMVECTOR r3 = XMVectorSet(0, 0, 0, 1);

	// RHS
	//XMVECTOR r0 = XMVectorSet(1.0f - 2.0f * (y2 + z2), 2 * (xy + sz)		  , 2 * (xz - sy)		   , 0);
	//XMVECTOR r1 = XMVectorSet(2 * (xy - sz)			 , 1.0f - 2.0f * (x2 + z2), 2 * (yz + sx)		   , 0);
	//XMVECTOR r2 = XMVectorSet(2 * (xz + sy)			 , 2 * (yz - sx)		  , 1.0f - 2.0f * (x2 + y2), 0);
	//XMVECTOR r3 = XMVectorSet(0						 , 0					  , 0					   , 1);

	m.r[0] = r0;
	m.r[1] = r1;
	m.r[2] = r2;
	m.r[3] = r3;
	return XMMatrixTranspose(m);
}

Quaternion_& Quaternion_::Normalize()
{
	float len = Len();
	if (len > 0.00001)
	{
		S = S / len;
		V.x = V.x / len;
		V.y = V.y / len;
		V.z = V.z / len;
	}
	return *this;
}

Vector3 Quaternion_::TransformVector(const Vector3 & v) const
{
	Quaternion_ pure(0.0f, v);
	Quaternion_ rotated = *this * pure * this->Conjugate();
	return Vector3(rotated.V);
}
