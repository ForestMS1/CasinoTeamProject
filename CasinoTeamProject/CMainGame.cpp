#include "pch.h"
#include "CMainGame.h"
#include "CTitleScene.h"
#include "CRussianRoulletScene.h"
#include "CCardPairScene.h"
#include "CSceneMgr.h"
#include "CObjMgr.h"
#include "CKeyMgr.h"
#include "CCollisionMgr.h"
#include "CCointoss.h"
#include "CSceneSlotMachine.h"
#include "CLineMgr.h"
#include "CSceneLineShoot.h"

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



	// ���Ŵ����� �� ���
	CScene* pScene = new CTitleScene;
	GETSINGLE(CSceneMgr)->CreateScene(L"Title", pScene);

  pScene = new CSceneSlotMachine;
	GETSINGLE(CSceneMgr)->CreateScene(L"RopeJump", pScene);

	pScene = new CSceneLineShoot;
	GETSINGLE(CSceneMgr)->CreateScene(L"LineShoot", pScene);

	pScene = new CRussianRoulletScene;
	GETSINGLE(CSceneMgr)->CreateScene(L"RussianRoullet", pScene);

	pScene = new CCardPairScene;
	GETSINGLE(CSceneMgr)->CreateScene(L"CardPairScene", pScene);
	
	pScene = new CCointoss;
	GETSINGLE(CSceneMgr)->CreateScene(L"CoinScene", pScene);

	
	//GETSINGLE(CSceneMgr)->ChangeScene(L"RussianRoullet");

	GETSINGLE(CSceneMgr)->ChangeScene(L"Title");
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

	// 충돌 처리 ?�시 (?�래처럼 추�??�면 ?�니??)
	//if (!GETSINGLE(CObjMgr)->GetObjLayer(OBJ_PLAYER).empty())
	//{
	//	CCollisionMgr::Collision_RectEx(GETSINGLE(CObjMgr)->GetObjLayer(OBJ_PLAYER), GETSINGLE(CObjMgr)->GetObjLayer(OBJ_ITEM));
	//	TODO : 충돌처리 추�?
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
		0,						// 복사 받을 공간??LEFT	
		0,						// 복사 받을 공간??TOP
		WINCX,					// 복사 받을 공간??가�?
		WINCY,					// 복사 받을 공간???�로 
		m_hBackDC,				// 복사 ??DC
		0,						// 복사???��?지??LEFT, TOP
		0,
		SRCCOPY);				// 그�?�?복사
}

void CMainGame::Release()
{
	// 매니?�????��
	CSceneMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	
	CLineMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
	ReleaseDC(g_hWnd, m_hBackDC);
}
