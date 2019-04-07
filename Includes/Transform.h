#pragma once
#include "stdafx.h"

class Transform
{
private:
	AltMath::Vector3<float>	m_position;
	AltMath::Quaternion		m_rotation;
	AltMath::Matrix4f		m_transformMatrix;

public:
	Transform(const AltMath::Vector3<float>& p_position, const AltMath::Quaternion& p_rotation );
	~Transform();

	void UpdateMatrix();
	void UpdateMatrix(Transform& p_other);

	void SetRotation(const AltMath::Quaternion& p_other);
	void SetPosition(const AltMath::Vector3<float>& p_other);
	void SetTransformMatrix(AltMath::Matrix4f&& p_other);

	const AltMath::Matrix4<float>&	GetTransformMatrix();
	const AltMath::Quaternion&		GetRotation() const;
};

