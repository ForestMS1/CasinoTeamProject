#include "pch.h"
#include "CShotEventObserver.h"

CShotEventObserver* CShotEventObserver::m_pInstance = nullptr;

CShotEventObserver::CShotEventObserver()
{
	m_pRevolver = nullptr;
	m_pMagazine = nullptr;
	m_bIsShot = false;
	m_dwLastShotTime = GetTickCount();
}

CShotEventObserver::~CShotEventObserver()
{

}

void CShotEventObserver::Update()
{
	if (m_dwLastShotTime + 1000 < GetTickCount())
		m_bIsShot = false;

	if (m_bIsShot)
		dynamic_cast<CMagazine*>(m_pMagazine)->Set_Angle(0.f);
}

void CShotEventObserver::Late_Update()
{

}

void CShotEventObserver::Release()
{

}