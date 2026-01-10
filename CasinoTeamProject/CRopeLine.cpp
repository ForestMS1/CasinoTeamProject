#include "pch.h"
#include "CRopeLine.h"

CRopeLine::CRopeLine()
{
	m_eRender = GAMEOBJECT;
}

CRopeLine::~CRopeLine()
{
}

void CRopeLine::Initialize()
{
	//m_vPoint[0] = { WINCX / 16 - 25, WINCY / 2 + 100, 0 };
	//m_vPoint[1] = { (WINCX - WINCX / 16) + 25, WINCY / 2 + 100, 0 };
	//m_vPoint[2] = { (WINCX - WINCX / 16) - 25 ,WINCY / 2 + 50, 0 };
	//m_vPoint[3] = { WINCX / 16 + 25, WINCY / 2 + 50, 0 };
	m_vPoint[0] = { (WINCX - WINCX / 16) + 25, WINCY / 2 + 50, 0 };
	m_vPoint[1] = { WINCX / 16 - 25 ,WINCY / 2 + 50, 0 };
	m_tInfo.vPos = { WINCX / 2, WINCY / 2 , 0.f };
	
}

int CRopeLine::Update()
{
	return 0;
}

void CRopeLine::Late_Update()
{
}

void CRopeLine::Render(HDC hDC)
{

	MoveToEx(hDC, m_vPoint[0].x ,m_vPoint[0].y,nullptr);
	LineTo(hDC, m_vPoint[1].x, m_vPoint[1].y);
	 
	MoveToEx(hDC, (WINCX - WINCX / 16) - 25, WINCY / 2 + 50, nullptr);
	LineTo(hDC, WINCX, WINCY);

	MoveToEx(hDC, WINCX / 16 + 25, WINCY / 2 +50, nullptr);
	LineTo(hDC, 0, WINCY);
}

void CRopeLine::Release()
{
}
