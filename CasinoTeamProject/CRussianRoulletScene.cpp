#include "pch.h"
#include "CRussianRoulletScene.h"
#include "CRevolver.h"
#include "CBullet.h"

CRussianRoulletScene::CRussianRoulletScene()
{
}

CRussianRoulletScene::~CRussianRoulletScene()
{
	Release();
}

void CRussianRoulletScene::Initialize()
{
	GETSINGLE(CObjMgr)->AddObject(OBJ_ITEM, new CRevolver);
	//GETSINGLE(CObjMgr)->AddObject(OBJ_ITEM, new CBullet);
}

int CRussianRoulletScene::Update()
{
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
}
