#include "pch.h"
#include "CFirstPerson.h"

CFirstPerson::CFirstPerson()
{
	m_eRender = GAMEOBJECT;
}

CFirstPerson::~CFirstPerson()
{
}

void CFirstPerson::Initialize()
{
	m_vPoint[0] = { (WINCX - WINCX / 16) - 25, WINCY / 2 - 50, 0 };
	m_vPoint[1] = { (WINCX - WINCX / 16) + 25, WINCY / 2 - 50, 0 };
	m_vPoint[2] = { (WINCX - WINCX / 16) + 25, WINCY / 2 + 50, 0 };
	m_vPoint[3] = { (WINCX - WINCX / 16) - 25, WINCY / 2 + 50, 0 };
	m_tInfo.vPos = { WINCX / 2, WINCY / 2 , 0.f };
}

int CFirstPerson::Update()
{
    return 0;
}

void CFirstPerson::Late_Update()
{
}

void CFirstPerson::Render(HDC hDC)
{

	MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);

	for (int i = 0; i < 4; ++i)
		LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y);

	LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);
}

void CFirstPerson::Release()
{
}
