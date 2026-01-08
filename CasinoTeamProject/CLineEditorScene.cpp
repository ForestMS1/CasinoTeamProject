#include "pch.h"
#include "CLineEditorScene.h"
#include "CLineMgr.h"

CLineEditorScene::CLineEditorScene()
{
}

CLineEditorScene::~CLineEditorScene()
{
	Release();
}

void CLineEditorScene::Initialize()
{
	GETSINGLE(CLineMgr)->Initialize();
}

int CLineEditorScene::Update()
{
	GETSINGLE(CLineMgr)->Update();
	return 0;
}

void CLineEditorScene::Late_Update()
{
	GETSINGLE(CLineMgr)->Late_Update();
}

void CLineEditorScene::Render(HDC hDC)
{
	GETSINGLE(CLineMgr)->Render(hDC);
}

void CLineEditorScene::Release()
{
	// 씬 나올때 ObjMgr에 있는 Obj들 지움
	GETSINGLE(CObjMgr)->DeleteAllLayer();

	CLineMgr::Destroy_Instance();
}
