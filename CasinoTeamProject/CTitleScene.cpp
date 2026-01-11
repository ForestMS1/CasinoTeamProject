#include "pch.h"
#include "CTitleScene.h"
#include "CTestCube.h"

#include "CLineMgr.h"
#include "CSceneSelectBtn.h"
#include "CObjMgr.h"
#include "CSceneMgr.h"

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
	//CTestCube* testCube = new CTestCube;
	//GETSINGLE(CObjMgr)->AddObject(OBJ_PLAYER, testCube);

	CSceneSelectBtn* pSelectBtn = new CSceneSelectBtn(L"Coin");
	pSelectBtn->Set_Pos(100.f, 100.f, 0.f);
	pSelectBtn->Initialize();
	GETSINGLE(CObjMgr)->AddObject(OBJ_ITEM, pSelectBtn);

	pSelectBtn = new CSceneSelectBtn(L"RopeJump");
	pSelectBtn->Set_Pos(300.f, 100.f, 0.f);
	pSelectBtn->Initialize();
	GETSINGLE(CObjMgr)->AddObject(OBJ_ITEM, pSelectBtn);

	pSelectBtn = new CSceneSelectBtn(L"LineShoot");
	pSelectBtn->Set_Pos(500.f, 100.f, 0.f);
	pSelectBtn->Initialize();
	GETSINGLE(CObjMgr)->AddObject(OBJ_ITEM, pSelectBtn);

	pSelectBtn = new CSceneSelectBtn(L"RussianRoullet");
	pSelectBtn->Set_Pos(100.f, 200.f, 0.f);
	pSelectBtn->Initialize();
	GETSINGLE(CObjMgr)->AddObject(OBJ_ITEM, pSelectBtn);

	pSelectBtn = new CSceneSelectBtn(L"CardPairScene");
	pSelectBtn->Set_Pos(300.f, 200.f, 0.f);
	pSelectBtn->Initialize();
	GETSINGLE(CObjMgr)->AddObject(OBJ_ITEM, pSelectBtn);

	pSelectBtn = new CSceneSelectBtn(L"CoinScene");
	pSelectBtn->Set_Pos(500.f, 200.f, 0.f);
	pSelectBtn->Initialize();
	GETSINGLE(CObjMgr)->AddObject(OBJ_ITEM, pSelectBtn);


}

int CTitleScene::Update()
{
	return 0;
}

void CTitleScene::Late_Update()
{
	list<CObj*> btnList = GETSINGLE(CObjMgr)->GetObjLayer(OBJ_ITEM);
	for (auto& btn : btnList)
	{
		CSceneSelectBtn* pBtn = dynamic_cast<CSceneSelectBtn*>(btn);
		if (pBtn->ChangeNextScene())
		{
			GETSINGLE(CSceneMgr)->ChangeScene(pBtn->Get_NextSceneName());
			break;
		}
	}
}

void CTitleScene::Render(HDC hDC)
{

}

void CTitleScene::Release()
{
	// 씬 나올때 ObjMgr에 있는 Obj들 지움
	GETSINGLE(CObjMgr)->DeleteAllLayer();
}
