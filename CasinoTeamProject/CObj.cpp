#include "pch.h"
#include "CObj.h"

CObj::CObj() : 
	m_bIsDead(false), 
	m_fSpeed(0.f),
	m_eRender(RENDER_END)
	
{
}

CObj::~CObj()
{
}
