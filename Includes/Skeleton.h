#pragma once
#include <vector>
#include <memory>
#include "stdafx.h"

class Skeleton
{
	std::vector<std::shared_ptr<class Bone>> m_bones;

public:
	Skeleton();
	~Skeleton() = default;

	void LoadBones(uint8_t p_index);
	void DrawSkeleton(float p_offset = 20.0f);
	
	void UpdateSkeletonPosition(const char* animName, float p_frameTime);
	void UpdateSkeleton(const char* animName, float p_frameTime);
	void AnimateMesh();
};

