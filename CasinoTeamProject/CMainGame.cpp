#include "pch.h"
#include "CMainGame.h"
#include "CTitleScene.h"
#include "CRussianRoulletScene.h"
#include "CCardPairScene.h"
#include "CSceneMgr.h"
#include "CObjMgr.h"
#include "CKeyMgr.h"
#include "CCollisionMgr.h"
<<<<<<< HEAD
#include "CCointoss.h"
=======
#include "CSceneSlotMachine.h"
#include "CLineMgr.h"
>>>>>>> master

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


<<<<<<< HEAD
	// æ¿∏≈¥œ¿˙ø° æ¿ µÓ∑œ
	CScene* pScene = new CTitleScene;
	GETSINGLE(CSceneMgr)->CreateScene(L"Title", pScene);
	CScene* pScene2 = new CCointoss;
	GETSINGLE(CSceneMgr)->CreateScene(L"Coin", pScene2);

	// √≥¿Ω ∫∏ø©¡Ÿ æ¿¿∏∑Œ ¿¸»Ø
	GETSINGLE(CSceneMgr)->ChangeScene(L"Coin");
=======
	// ?¨Îß§?àÏ??????±Î°ù
	//CScene* pScene = new CTitleScene;
	CScene* pScene = new CSceneSlotMachine;
	GETSINGLE(CSceneMgr)->CreateScene(L"RopeJump", pScene);

	pScene = new CRussianRoulletScene;
	GETSINGLE(CSceneMgr)->CreateScene(L"RussianRoullet", pScene);

	pScene = new CCardPairScene;
	GETSINGLE(CSceneMgr)->CreateScene(L"CardPairScene", pScene);

	GETSINGLE(CSceneMgr)->ChangeScene(L"RussianRoullet");

>>>>>>> master
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

	// Ï∂©Îèå Ï≤òÎ¶¨ ?àÏãú (?ÑÎûòÏ≤òÎüº Ï∂îÍ??òÎ©¥ ?©Îãà??)
	//if (!GETSINGLE(CObjMgr)->GetObjLayer(OBJ_PLAYER).empty())
	//{
	//	CCollisionMgr::Collision_RectEx(GETSINGLE(CObjMgr)->GetObjLayer(OBJ_PLAYER), GETSINGLE(CObjMgr)->GetObjLayer(OBJ_ITEM));
	//	TODO : Ï∂©ÎèåÏ≤òÎ¶¨ Ï∂îÍ?
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

	BitBlt(m_hDC,				// Î≥µÏÇ¨ Î∞õÏùÑ DC
		0,						// Î≥µÏÇ¨ Î∞õÏùÑ Í≥µÍ∞Ñ??LEFT	
		0,						// Î≥µÏÇ¨ Î∞õÏùÑ Í≥µÍ∞Ñ??TOP
		WINCX,					// Î≥µÏÇ¨ Î∞õÏùÑ Í≥µÍ∞Ñ??Í∞ÄÎ°?
		WINCY,					// Î≥µÏÇ¨ Î∞õÏùÑ Í≥µÍ∞Ñ???∏Î°ú 
		m_hBackDC,				// Î≥µÏÇ¨ ??DC
		0,						// Î≥µÏÇ¨???¥Î?ÏßÄ??LEFT, TOP
		0,
		SRCCOPY);				// Í∑∏Î?Î°?Î≥µÏÇ¨
}

void CMainGame::Release()
{
	// Îß§Îãà?Ä????†ú
	CSceneMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	
	CLineMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
	ReleaseDC(g_hWnd, m_hBackDC);
}
