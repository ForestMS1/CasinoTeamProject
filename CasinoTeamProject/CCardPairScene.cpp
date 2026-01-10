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
    GETSINGLE(CCardMgr)->Render(hDC);
}

void CCardPairScene::Release()
{
    CCardMgr::Destroy_Instance();
}
