
#ifndef _QK3DQUATERNION_H_
#define _QK3DQUATERNION_H_

#include "SimpleMath.h"
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


#endif