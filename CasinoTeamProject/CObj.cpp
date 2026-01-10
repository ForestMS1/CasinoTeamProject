#include "pch.h"
#include "CObj.h"

CObj::CObj() : 
	m_bIsDead(false), 
	m_fSpeed(0.f),
	m_eRender(RENDER_END),
	m_bScore(false),
	m_bJump(false)
{
}

CObj::~CObj()
{
}
