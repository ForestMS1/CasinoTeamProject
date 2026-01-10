#include "pch.h"
#include "CTitleScene.h"
#include "CTestCube.h"

#include "CLineMgr.h"

CTitleScene::CTitleScene()
{
}

CTitleScene::~CTitleScene()
{
	Release();
}

void CTitleScene::Initialize()
{
	// 씬에서 Obj만들고 ObjMgr에 넣어주면 알아서 Update, Late_Update, Render 해줍니다

	// 프레임워크 테스트용 객체입니다.
	CTestCube* testCube = new CTestCube;
	GETSINGLE(CObjMgr)->AddObject(OBJ_PLAYER, testCube);
}

int CTitleScene::Update()
{

	return 0;
}

void CTitleScene::Late_Update()
{

}

void CTitleScene::Render(HDC hDC)
{

}

void CTitleScene::Release()
{
	// 씬 나올때 ObjMgr에 있는 Obj들 지움
	GETSINGLE(CObjMgr)->DeleteAllLayer();
}
