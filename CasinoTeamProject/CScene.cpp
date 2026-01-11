#include "pch.h"
#include "CScene.h"
#include "CSceneMgr.h"
CScene::CScene() : pBtn(nullptr)
{

}

CScene::~CScene()
{
	Release();
}

void CScene::Initialize()
{
	pBtn = new CGoTitleBtn;
	pBtn->Initialize();
	GETSINGLE(CObjMgr)->AddObject(OBJ_BACK_BUTTON, pBtn);
}

int CScene::Update()
{

	return 0;
}

void CScene::Late_Update()
{
	if (pBtn->ChangeNextScene())
	{
		GETSINGLE(CSceneMgr)->ChangeScene(L"Title");
	}
}

void CScene::Render(HDC hDC)
{
}

void CScene::Release()
{

}