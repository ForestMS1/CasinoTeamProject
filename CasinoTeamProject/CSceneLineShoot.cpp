#include "pch.h"
#include "CSceneLineShoot.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPlayerL.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CLineShoot.h"
CSceneLineShoot::CSceneLineShoot()
{
}

CSceneLineShoot::~CSceneLineShoot()
{
}

void CSceneLineShoot::Initialize()
{
    GETSINGLE(CObjMgr)->AddObject(OBJ_LINE, CAbstractFactory<CLineShoot>::Create());
    GETSINGLE(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayerL>::Create());
}

int CSceneLineShoot::Update()
{
    if (GETSINGLE(CKeyMgr)->Get_KeyState('O'))
    {
        GETSINGLE(CSceneMgr)->ChangeScene(L"LineShoot");
    }
	return 0;
}

void CSceneLineShoot::Late_Update()
{
}

void CSceneLineShoot::Render(HDC hDC)
{
}

void CSceneLineShoot::Release()
{
    GETSINGLE(CObjMgr)->DeleteLayerObj(OBJ_PLAYER);
    GETSINGLE(CObjMgr)->DeleteLayerObj(OBJ_LINE);
}
