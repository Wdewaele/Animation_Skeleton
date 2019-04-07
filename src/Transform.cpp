#include "Transform.h"

Transform::Transform(const AltMath::Vector3<float>& p_position, const AltMath::Quaternion& p_rotation)
	: m_position(p_position),  m_rotation(p_rotation)
{
	this->UpdateMatrix();
}


Transform::~Transform()
{}

void Transform::UpdateMatrix()
{
	if (!this->m_rotation.IsNormalized())
		this->m_rotation.Normalize();
	this->m_transformMatrix = AltMath::Matrix4f::Translation(this->m_position) * this->m_rotation.ToMatrix4();
}

void Transform::UpdateMatrix(Transform & p_other)
{
	if (!this->m_rotation.IsNormalized())
		this->m_rotation.Normalize();
	this->m_transformMatrix = p_other.GetTransformMatrix() *  (AltMath::Matrix4f::Translation(this->m_position) * this->m_rotation.ToMatrix4());
}

void Transform::SetRotation(const AltMath::Quaternion& p_other)
{	
	this->m_rotation = p_other;
	this->UpdateMatrix();
}

void Transform::SetPosition(const AltMath::Vector3<float>& p_other)
{
	this->m_position = p_other;
	this->UpdateMatrix();
}

void Transform::SetTransformMatrix(AltMath::Matrix4f&& p_other)
{
	this->m_transformMatrix = p_other;
	this->UpdateMatrix();
}

 const AltMath::Matrix4<float>& Transform::GetTransformMatrix()
{
	 return this->m_transformMatrix;
}

const AltMath::Quaternion& Transform::GetRotation() const
{
	return this->m_rotation;
}
