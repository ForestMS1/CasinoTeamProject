#include "pch.h"
#include "CCardPairScene.h"
#include "CCardMgr.h"
CCardPairScene::CCardPairScene()
{
}

CCardPairScene::~CCardPairScene()
{
    Release();
}

void CCardPairScene::Initialize()
{
    GETSINGLE(CObjMgr)->AddObject(OBJ_ITEM, CAbstractFactory<CCard>::Create(D3DXVECTOR3(WINCX, WINCY, 0.f)));
    GETSINGLE(CCardMgr)->Initialize();
}

int CCardPairScene::Update()
{
    GETSINGLE(CCardMgr)->Update();
    return 0;
}

void CCardPairScene::Late_Update()
{
    GETSINGLE(CCardMgr)->Late_Update();
}

void CCardPairScene::Render(HDC hDC)
{
}

void CCardPairScene::Release()
{
    CCardMgr::Destroy_Instance();
}
