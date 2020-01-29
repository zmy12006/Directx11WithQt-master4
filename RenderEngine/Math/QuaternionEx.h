
#ifndef _QK3DQUATERNION_H_
#define _QK3DQUATERNION_H_

#include "SimpleMath.h"

#define DEG2RAD (XM_PI / 180.0f)
#define RAD2DEG (180.0f / XM_PI)

using namespace DirectX;
using namespace DirectX::SimpleMath;

class QuaternionEx : public Quaternion
{
public:
// 	void set(const Vector3& axis, float angle);
// 	void set( Matrix& m);
// 	void set(const Vector3& angle);
// 	static void createFromAxisAngle(const Vector3& axis, float angle, Quaternion* dst);
// 	static void createFromRotationMatrix( Matrix& m, Quaternion* dst);

	// Static functions
	static Quaternion CreateFromAxisAngle(const Vector3& axis, float angle);
	static Quaternion CreateFromYawPitchRoll(float yaw, float pitch, float roll);
	static Quaternion CreateFromRotationMatrix(const Matrix& M);

	static void GetAxisAngle(const Quaternion& q, Vector3& axis, float& angle);
	static Quaternion SetEulerAngle(float yaw, float pitch, float roll);
	static Vector3 GetEulerAngle(Quaternion q);

protected:
private:
};

class Quaternion_
{
public:
	static Quaternion_ Identity();
	static Quaternion_ FromAxisAngle(const XMVECTOR& axis, const float angle);
	static Quaternion_ Lerp(const Quaternion_& from, const Quaternion_& to, float t);
	static Quaternion_ Slerp(const Quaternion_& from, const Quaternion_& to, float t);
	static Vector3 ToEulerRad(const Quaternion_& Q);
	static Vector3 ToEulerDeg(const Quaternion_& Q);
	//-----------------------------------------------
	//Quaternion(float roll, float pitch, float yaw);
	//Quaternion(const vec3& rollPitchYaw);
	Quaternion_(const XMMATRIX& rotMatrix);
	Quaternion_(float s, const XMVECTOR& v);
	//-----------------------------------------------
	Quaternion_  operator+(const Quaternion_& q) const;
	Quaternion_  operator*(const Quaternion_& q) const;
	Quaternion_  operator*(float c) const;
	bool		operator==(const Quaternion_& q) const;
	float		Dot(const Quaternion_& q) const;
	float		Len() const;
	Quaternion_  Inverse() const;
	Quaternion_  Conjugate() const;
	XMMATRIX	Matrix() const;
	Quaternion_&	Normalize();

	Vector3 TransformVector(const Vector3& v) const;

private:	// used by operator()s
	Quaternion_(float s, const Vector3& v);
	Quaternion_();

public:
	// Q = [S, <V>]
	Vector3 V;
	float S;
};


#endif