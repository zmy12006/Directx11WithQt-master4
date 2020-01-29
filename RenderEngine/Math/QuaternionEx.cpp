
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