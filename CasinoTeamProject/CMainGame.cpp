#include "pch.h"
#include "CMainGame.h"
#include "CTitleScene.h"
#include "CRussianRoulletScene.h"
#include "CSceneMgr.h"
#include "CObjMgr.h"
#include "CKeyMgr.h"
#include "CCollisionMgr.h"
#include "CLineMgr.h"

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


	// 씬매니저에 씬 등록
	CScene* pScene = new CTitleScene;
	GETSINGLE(CSceneMgr)->CreateScene(L"Title", pScene);

	pScene = new CRussianRoulletScene;
	GETSINGLE(CSceneMgr)->CreateScene(L"RussianRoullet", pScene);


	// 처음 보여줄 씬으로 전환
	GETSINGLE(CSceneMgr)->ChangeScene(L"RussianRoullet");

	GETSINGLE(CObjMgr)->Initialize();
}

void CMainGame::Update()
{
	GETSINGLE(CSceneMgr)->Update();
	GETSINGLE(CObjMgr)->Update();
}

void CMainGame::Late_Update()
{
	GETSINGLE(CSceneMgr)->Late_Update();
	GETSINGLE(CKeyMgr)->Late_Update();
	GETSINGLE(CObjMgr)->Late_Update();

	// 충돌 처리 예시 (아래처럼 추가하면 됩니다.)
	//if (!GETSINGLE(CObjMgr)->GetObjLayer(OBJ_PLAYER).empty())
	//{
	//	CCollisionMgr::Collision_RectEx(GETSINGLE(CObjMgr)->GetObjLayer(OBJ_PLAYER), GETSINGLE(CObjMgr)->GetObjLayer(OBJ_ITEM));
	//	TODO : 충돌처리 추가
	//}
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

	GETSINGLE(CSceneMgr)->Render(m_hBackDC);
	GETSINGLE(CObjMgr)->Render(m_hBackDC);

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
	// 매니저들 삭제
	CSceneMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CLineMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
	ReleaseDC(g_hWnd, m_hBackDC);
}
