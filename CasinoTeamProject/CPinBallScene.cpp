#include "pch.h"
#include "CPinBallScene.h"

CPinBallScene::CPinBallScene()
{
}

CPinBallScene::~CPinBallScene()
{
	Release();
}

void CPinBallScene::Initialize()
{
}

int CPinBallScene::Update()
{
	return 0;
}

void CPinBallScene::Late_Update()
{
}

void CPinBallScene::Render(HDC hDC)
{
}

void CPinBallScene::Release()
{
	// 씬 나올때 ObjMgr에 있는 Obj들 지움
	GETSINGLE(CObjMgr)->DeleteAllLayer();
}
