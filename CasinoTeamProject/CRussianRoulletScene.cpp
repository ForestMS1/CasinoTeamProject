#include "pch.h"
#include "CRussianRoulletScene.h"
#include "CRevolver.h"
#include "CBullet.h"
#include "CRRPlayer.h"
#include "CMagazine.h"
#include "CShotEventObserver.h"

CRussianRoulletScene::CRussianRoulletScene()
{
}

CRussianRoulletScene::~CRussianRoulletScene()
{
	Release();
}

void CRussianRoulletScene::Initialize()
{
	CObj* pRevolver = new CRevolver;
	CObj* pMagazine = new CMagazine;
	GETSINGLE(CObjMgr)->AddObject(OBJ_ITEM, pRevolver);
	GETSINGLE(CObjMgr)->AddObject(OBJ_ITEM, pMagazine);
	GETSINGLE(CShotEventObserver)->Initialize(pRevolver, pMagazine);


	GETSINGLE(CObjMgr)->AddObject(OBJ_ITEM, new CRRPlayer);
}

int CRussianRoulletScene::Update()
{
	GETSINGLE(CShotEventObserver)->Update();
	return 0;
}

void CRussianRoulletScene::Late_Update()
{
}

void CRussianRoulletScene::Render(HDC hDC)
{
}

void CRussianRoulletScene::Release()
{
	CShotEventObserver::Destroy_Instance();
}
