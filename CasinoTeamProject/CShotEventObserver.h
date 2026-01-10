#pragma once
#include "CRevolver.h"
#include "CMagazine.h"
class CShotEventObserver
{
	SINGLE(CShotEventObserver)
public:
	void Initialize(CObj* _pRevolver, CObj* _pMagazine) { m_pRevolver = _pRevolver; m_pMagazine = _pMagazine; }
	void Update();
	void Late_Update();
	void Release();

public:
	void Set_Shot(bool _isShot)							{ m_bIsShot = _isShot; m_dwLastShotTime = GetTickCount();}
private:
	CObj* m_pRevolver;
	CObj* m_pMagazine;

	bool  m_bIsShot;
	DWORD m_dwLastShotTime;
};

