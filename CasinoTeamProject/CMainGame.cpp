#include "pch.h"
#include "CMainGame.h"

CMainGame::CMainGame() : m_iFps(0), m_dwLastTime(GetTickCount())
{
	ZeroMemory(&m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);
	m_hBackDC = CreateCompatibleDC(m_hDC);
	m_hBitMap = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	HBITMAP hBit = (HBITMAP)SelectObject(m_hBackDC, m_hBitMap);
	DeleteObject(hBit);
}

void CMainGame::Update()
{
}

void CMainGame::Late_Update()
{
}

void CMainGame::Render()
{
	++m_iFps;

	DWORD curTime = GetTickCount();
	if (m_dwLastTime + 1000 < curTime)
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFps);
		m_iFps = 0;

		SetWindowText(g_hWnd, m_szFPS);

		m_dwLastTime = curTime;
	}

	BitBlt(m_hDC,				// 복사 받을 DC
		0,						// 복사 받을 공간의 LEFT	
		0,						// 복사 받을 공간의 TOP
		WINCX,					// 복사 받을 공간의 가로 
		WINCY,					// 복사 받을 공간의 세로 
		m_hBackDC,				// 복사 할 DC
		0,						// 복사할 이미지의 LEFT, TOP
		0,
		SRCCOPY);				// 그대로 복사
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);
	ReleaseDC(g_hWnd, m_hBackDC);
}
