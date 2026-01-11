#include "pch.h"
#include "CRussianRoulletScene.h"
#include "CRevolver.h"
#include "CBullet.h"
#include "CRRPlayer.h"
#include "CMagazine.h"
#include "CShotEventObserver.h"
#include "CCollisionMgr.h"

CRussianRoulletScene::CRussianRoulletScene()
{
}

CRussianRoulletScene::~CRussianRoulletScene()
{
	Release();
}

void CRussianRoulletScene::Initialize()
{
	__super::Initialize();

	CObj* pRevolver = new CRevolver;
	CObj* pMagazine = new CMagazine;
	pRevolver->Initialize();
	pMagazine->Initialize();
	GETSINGLE(CObjMgr)->AddObject(OBJ_ITEM, pRevolver);
	GETSINGLE(CObjMgr)->AddObject(OBJ_ITEM, pMagazine);
	GETSINGLE(CShotEventObserver)->Initialize(pRevolver, pMagazine);

	GETSINGLE(CObjMgr)->AddObject(OBJ_PLAYER, 
		CAbstractFactory<CRRPlayer>::Create(D3DXVECTOR3((WINCX >> 1) + 300.f, WINCY >> 1, 0.f)));
	GETSINGLE(CObjMgr)->AddObject(OBJ_PLAYER,
		CAbstractFactory<CRRPlayer>::Create(D3DXVECTOR3((WINCX >> 1) - 300.f, WINCY >> 1, 0.f)));
}

int CRussianRoulletScene::Update()
{
	GETSINGLE(CShotEventObserver)->Update();
	return 0;
}

void CRussianRoulletScene::Late_Update()
{
	//	총알과 사람 충돌처리
	CCollisionMgr::Collision_Rect(GETSINGLE(CObjMgr)->GetObjLayer(OBJ_PLAYER), GETSINGLE(CObjMgr)->GetObjLayer(OBJ_ITEM));
	__super::Late_Update();
}

void CRussianRoulletScene::Render(HDC hDC)
{
}

void CRussianRoulletScene::Release()
{
	CShotEventObserver::Destroy_Instance();
	GETSINGLE(CObjMgr)->DeleteAllLayer();
}
