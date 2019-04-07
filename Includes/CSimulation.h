#include "stdafx.h"
#include "Engine.h"

#include "Simulation.h"
#include "Skeleton.h"
#pragma once
class CSimulation : public ISimulation
{
private :

	float	m_timeCalculator	= 0.0f;
	size_t	keyCount			= 0;
	uint8_t m_keyFrame			= 0;
	Skeleton* m_skel;


public :
	CSimulation();
	~CSimulation();

	virtual void Init() override;
	virtual void Update(float frameTime) override;
};

