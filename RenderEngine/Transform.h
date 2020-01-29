#pragma once
#include "Math/SimpleMath.h"
#include "Math/QuaternionEx.h"

using namespace DirectX;

struct Transform
{
public:

	//----------------------------------------------------------------------------------------------------------------
	// CONSTRUCTOR / DESTRUCTOR
	//----------------------------------------------------------------------------------------------------------------
	Transform(const SimpleMath::Vector3&			position = SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
		const Quaternion_&	rotation = Quaternion_::Identity(),
		const SimpleMath::Vector3&			scale = SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
	~Transform();
	Transform& operator=(const Transform&);

	//----------------------------------------------------------------------------------------------------------------
	// GETTERS & SETTERS
	//----------------------------------------------------------------------------------------------------------------
	inline void SetXRotationDeg(float xDeg) { _rotation = Quaternion_::FromAxisAngle(SimpleMath::Vector3::Right, xDeg * DEG2RAD); }
	inline void SetYRotationDeg(float yDeg) { _rotation = Quaternion_::FromAxisAngle(SimpleMath::Vector3::Up, yDeg * DEG2RAD); }
	inline void SetZRotationDeg(float zDeg) { _rotation = Quaternion_::FromAxisAngle(SimpleMath::Vector3::Forward, zDeg * DEG2RAD); }
	inline void SetScale(float x, float y, float z) { _scale = SimpleMath::Vector3(x, y, z); }
	inline void SetScale(const SimpleMath::Vector3& scl) { _scale = scl; }
	inline void SetUniformScale(float s) { _scale = SimpleMath::Vector3(s, s, s); }
	inline void SetPosition(float x, float y, float z) { _position = SimpleMath::Vector3(x, y, z); }
	inline void SetPosition(const SimpleMath::Vector3& pos) { _position = pos; }

	//----------------------------------------------------------------------------------------------------------------
	// TRANSFORMATIONS
	//----------------------------------------------------------------------------------------------------------------
	void Translate(const SimpleMath::Vector3& translation);
	void Translate(float x, float y, float z);
	void Scale(const SimpleMath::Vector3& scl);

	void RotateAroundPointAndAxis(const SimpleMath::Vector3& axis, float angle, const SimpleMath::Vector3& point);
	inline void RotateAroundAxisRadians(const SimpleMath::Vector3& axis, float angle) { RotateInWorldSpace(Quaternion_::FromAxisAngle(axis, angle)); }
	inline void RotateAroundAxisDegrees(const SimpleMath::Vector3& axis, float angle) { RotateInWorldSpace(Quaternion_::FromAxisAngle(axis, angle * DEG2RAD)); }

	inline void RotateAroundLocalXAxisDegrees(float angle) { RotateInLocalSpace(Quaternion_::FromAxisAngle(SimpleMath::Vector3(1.0f,0.0f,0.0f), std::forward<float>(angle * DEG2RAD))); }
	inline void RotateAroundLocalYAxisDegrees(float angle) { RotateInLocalSpace(Quaternion_::FromAxisAngle(SimpleMath::Vector3(0.0f, 1.0f, 0.0f), std::forward<float>(angle * DEG2RAD))); }
	inline void RotateAroundLocalZAxisDegrees(float angle) { RotateInLocalSpace(Quaternion_::FromAxisAngle(SimpleMath::Vector3(0.0f, 0.0f, 1.0f), std::forward<float>(angle * DEG2RAD))); }
	inline void RotateAroundGlobalXAxisDegrees(float angle) { RotateAroundAxisDegrees(SimpleMath::Vector3(1.0f, 0.0f, 0.0f), std::forward<float>(angle)); }
	inline void RotateAroundGlobalYAxisDegrees(float angle) { RotateAroundAxisDegrees(SimpleMath::Vector3(0.0f, 1.0f, 0.0f), std::forward<float>(angle)); }
	inline void RotateAroundGlobalZAxisDegrees(float angle) { RotateAroundAxisDegrees(SimpleMath::Vector3(0.0f, 0.0f, 1.0f), std::forward<float>(angle)); }

	inline void RotateInWorldSpace(const Quaternion_& q) { _rotation = q * _rotation; }
	inline void RotateInLocalSpace(const Quaternion_& q) { _rotation = _rotation * q; }


	XMMATRIX WorldTransformationMatrix() const;
	XMMATRIX WorldTransformationMatrix_NoScale() const;
	static XMMATRIX NormalMatrix(const XMMATRIX& world);
	XMMATRIX RotationMatrix() const;

	//----------------------------------------------------------------------------------------------------------------
	// DATA
	//----------------------------------------------------------------------------------------------------------------
	SimpleMath::Vector3				_position;
	Quaternion_			_rotation;
	SimpleMath::Vector3				_scale;
	const SimpleMath::Vector3			_originalPosition;
	const Quaternion_	_originalRotation;
};
