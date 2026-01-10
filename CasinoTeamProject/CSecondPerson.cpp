#include "pch.h"
#include "CSecondPerson.h"

CSecondPerson::CSecondPerson()
{
	m_eRender = GAMEOBJECT;
}

CSecondPerson::~CSecondPerson()
{
}

void CSecondPerson::Initialize()
{
	m_vPoint[0] = { WINCX / 16 - 25, WINCY / 2 - 50, 0 };
	m_vPoint[1] = { WINCX / 16 + 25, WINCY / 2 - 50, 0 };
	m_vPoint[2] = { WINCX / 16 + 25, WINCY / 2 + 50, 0 };
	m_vPoint[3] = { WINCX / 16 - 25, WINCY / 2 + 50, 0 };
	m_tInfo.vPos = { WINCX / 2, WINCY / 2 , 0.f };
}

int CSecondPerson::Update()
{
    return 0;
}

void CSecondPerson::Late_Update()
{
}

void CSecondPerson::Render(HDC hDC)
{
	MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);

	for (int i = 0; i < 4; ++i)
		LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y);

	LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);
}

void CSecondPerson::Release()
{
}
