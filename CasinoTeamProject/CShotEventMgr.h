#pragma once
#include "CRevolver.h"
#include "CMagazine.h"
class CShotEventMgr
{
	SINGLE(CShotEventMgr)
public:
	void Initialize(CObj* _pRevolver, CObj* _pMagazine) { m_pRevolver = _pRevolver; m_pMagazine = _pMagazine; }
	void Update();
	void Late_Update();
	void Release();
private:
	CObj* m_pRevolver;
	CObj* m_pMagazine;
};

