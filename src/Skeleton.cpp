#include "Skeleton.h"

#include "Engine.h"
#include "Bone.h"


Skeleton::Skeleton()
{
	this->m_bones.resize(61);
	for (uint8_t i = 0; i < m_bones.size(); ++i)
	{
		if (!this->m_bones[i])
			this->LoadBones(i);
	}
}

void Skeleton::LoadBones(uint8_t p_index)
{
	AltMath::Vector3f pos;
	AltMath::Vector4f rot;
	int parent = 0;
	parent = GetSkeletonBoneParentIndex(p_index);
	GetSkeletonBoneLocalBindTransform(p_index, pos.x, pos.y, pos.z, rot.w, rot.x, rot.y, rot.z);
	if (parent > -1)
	{
		if (!this->m_bones[parent])
			this->LoadBones(parent);

		this->m_bones[p_index] = (this->m_bones.at(parent)->AddChild(pos, AltMath::Quaternion(rot.x, rot.y, rot.z, rot.w)));
	}
	else
		this->m_bones[p_index] = std::make_shared<Bone>(pos, AltMath::Quaternion(rot.x, rot.y, rot.z, rot.w));
}

void Skeleton::DrawSkeleton(float p_offset)
{	
	for (uint8_t i = 0; i < m_bones.size(); ++i)
	{
		m_bones[i]->Draw(p_offset);
	}
}

void Skeleton::UpdateSkeletonPosition(const char* animName, float p_frameTime)
{
	AltMath::Vector3f pos;
	AltMath::Vector4f rot;
	for (uint8_t boneIndex = 0; boneIndex < m_bones.size(); ++boneIndex)
	{
		GetAnimLocalBoneTransform(animName, boneIndex, static_cast<int>(p_frameTime), pos.x, pos.y, pos.z, rot.w, rot.x, rot.y, rot.z);
		this->m_bones[boneIndex]->SetLocalTransform(pos, AltMath::Quaternion(rot.x, rot.y, rot.z, rot.w));
	}
}

void Skeleton::UpdateSkeleton(const char* animName, float p_frameTime)
{
	if (animName)
	{
		m_bones[0]->NotifyChildToUpdate();
		UpdateSkeletonPosition(animName, p_frameTime);
	}
}

void Skeleton::AnimateMesh()
{
	AltMath::Matrix4f mat;
	float matrixToSend[16 * 64];

	for(uint8_t i = 0; i < m_bones.size(); ++i)
	{
		memcpy(&matrixToSend[i * 16], this->m_bones[i]->GetGlobalAnimatedMesh().elements, 16 * sizeof(float));
	}
	SetSkinningPose(matrixToSend, m_bones.size());
}