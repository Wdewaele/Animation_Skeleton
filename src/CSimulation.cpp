#include "CSimulation.h"

CSimulation::CSimulation()
{
	
}


CSimulation::~CSimulation()
{}

void CSimulation::Init()
{
	int spine01 = GetSkeletonBoneIndex("spine_01");
	int spineParent = GetSkeletonBoneParentIndex(spine01);
	const char* spineParentName = GetSkeletonBoneName(spineParent);

	float posX, posY, posZ, quatW, quatX, quatY, quatZ;
	keyCount = GetAnimKeyCount("ThirdPersonWalk.anim");
	GetAnimLocalBoneTransform("ThirdPersonWalk.anim", spineParent, keyCount / 2, posX, posY, posZ, quatW, quatX, quatY, quatZ);

	printf("Spine parent bone : %s\n", spineParentName);
	printf("==== Anim key count : %ld\n", keyCount);
	printf("Anim key : pos(%.2f,%.2f,%.2f) rotation quat(%.10f,%.10f,%.10f,%.10f)\n", posX, posY, posZ, quatW, quatX, quatY, quatZ);
	m_skel = new Skeleton();
}

void CSimulation::Update(float frameTime)
{
	// X axis
	DrawLine(0, 0, 0, 100, 0, 0, 1, 0, 0);

	// Y axis
	DrawLine(0, 0, 0, 0, 100, 0, 0, 1, 0);

	// Z axis
	DrawLine(0, 0, 0, 0, 0, 100, 0, 0, 1);

	m_timeCalculator += frameTime;	
	if (m_timeCalculator > 1.0f / keyCount)
	{
		m_keyFrame++;
		m_timeCalculator = 0;
	}
	if (m_keyFrame == keyCount)
	{
		m_keyFrame = 0;
	}
	m_skel->UpdateSkeleton("ThirdPersonWalk.anim", m_keyFrame);
	m_skel->DrawSkeleton(20.0f);
	m_skel->AnimateMesh();
}
