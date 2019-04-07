#include "stdafx.h"
#include "Engine.h"

#include "Bone.h"

Bone::Bone(const AltMath::Vector3<float>& p_position, const AltMath::Quaternion& p_rotation, std::shared_ptr<Bone>& p_parent) :
	m_local(p_position, p_rotation), m_Tpose(p_position, p_rotation), m_parent(p_parent)
{}

Bone::Bone(const AltMath::Vector3<float>& p_position, const AltMath::Quaternion & p_rotation):
	m_local(p_position, p_rotation), m_Tpose(p_position, p_rotation),
	m_needUpdate(true)
{}

Bone::~Bone()
{}

void Bone::Draw(float p_offset)
{
	if (HasParent())
	{
		AltMath::Vector3f pos = this->GetGlobalPosition();
		AltMath::Vector3f parentPos = this->m_parent->GetGlobalPosition();

		DrawCross(pos, p_offset);
		DrawLine(pos.x, pos.y - p_offset, pos.z,
			parentPos.x, parentPos.y - p_offset, parentPos.z,
			0.0f, 1.0f, 0.6f);
	}
}

void Bone::DrawCross(AltMath::Vector3f& p_pos, float p_offset)
{
	DrawLine(p_pos.x - 2, p_pos.y - p_offset, p_pos.z, p_pos.x + 2, p_pos.y - p_offset, p_pos.z, 1.0f, 0.f, 0.0f);
	DrawLine(p_pos.x, p_pos.y - p_offset - 2, p_pos.z, p_pos.x, p_pos.y - p_offset + 2, p_pos.z, 1.0f, 0.f, 0.0f);
	DrawLine(p_pos.x, p_pos.y - p_offset, p_pos.z - 2, p_pos.x, p_pos.y - p_offset, p_pos.z + 2, 1.0f, 0.f, 0.0f);
}

std::shared_ptr<Bone> Bone::AddChild(const AltMath::Vector3<float>& p_position, const AltMath::Quaternion& p_rotation)
{
	m_childs.emplace_back(std::make_shared<Bone>(p_position, p_rotation,shared_from_this()));
	return m_childs.back();
}

Transform Bone::GetLocalTransform()
{
	return this->m_local;
}

void Bone::NotifyChildToUpdate()
{
	for (const std::shared_ptr<Bone>& child : this->m_childs)
	{
		child->SetNeedUpdate(true);
	}
}

void Bone::SetNeedUpdate(bool p_needUpdate)
{
	this->m_needUpdate = p_needUpdate;
}

void Bone::SetLocalTransform(const AltMath::Vector3f& p_pos, AltMath::Quaternion p_rot)
{
	if (m_needUpdate)
	{
		this->m_local.SetPosition(p_pos);
		this->m_local.SetRotation(p_rot);
		this->m_local.UpdateMatrix(m_Tpose);
		this->NotifyChildToUpdate();
	}
	m_needUpdate = false;
}

AltMath::Matrix4f Bone::GetGlobalAnimatedMesh()
{
	return (this->GetGlobalTransform() * this->GetGlobalTpose().Inverse());
}

AltMath::Matrix4f Bone::GetGlobalTpose()
{
	return (this->m_parent) ? this->m_parent->GetGlobalTpose() * this->m_Tpose.GetTransformMatrix() : this->m_Tpose.GetTransformMatrix();
}

AltMath::Vector3f Bone::GetGlobalPosition()
{
	return {this->GetGlobalTransform()(0, 3), this->GetGlobalTransform()(1, 3), this->GetGlobalTransform()(2, 3)};
}

AltMath::Matrix4f Bone::GetGlobalTransform()
{
	return (this->m_parent) ? this->m_parent->GetGlobalTransform() * this->m_local.GetTransformMatrix() : this->m_local.GetTransformMatrix();
}

std::shared_ptr<Bone> Bone::GetParent() const
{
	return this->m_parent;
}

bool Bone::HasParent() const
{
	return static_cast<bool>(this->m_parent);
}

