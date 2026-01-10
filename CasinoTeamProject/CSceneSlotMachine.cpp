#include "pch.h"
#include "CSceneSlotMachine.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CFirstPerson.h"
#include "CSecondPerson.h"
#include "CRope.h"
#include "CRopeLine.h"
#include "CPlayerR.h"
#include "CCollisionMgr.h"
CSceneSlotMachine::CSceneSlotMachine()
{
}

CSceneSlotMachine::~CSceneSlotMachine()
{
}

void CSceneSlotMachine::Initialize()
{
    GETSINGLE(CObjMgr)->AddObject(OBJ_ROLLING, CAbstractFactory<CFirstPerson>::Create());
    GETSINGLE(CObjMgr)->AddObject(OBJ_ROLLING, CAbstractFactory<CSecondPerson>::Create());

    GETSINGLE(CObjMgr)->AddObject(OBJ_ROLLING, CAbstractFactory<CRopeLine>::Create());
    GETSINGLE(CObjMgr)->AddObject(OBJ_ROPE, CAbstractFactory<CRope>::Create());
    GETSINGLE(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayerR>::Create());

}

int CSceneSlotMachine::Update()
{
    return 0;
}

void CSceneSlotMachine::Late_Update()
{
    CCollisionMgr::Collision_Rope(GETSINGLE(CObjMgr)->GetObjLayer(OBJ_ROPE).front(), GETSINGLE(CObjMgr)->GetObjLayer(OBJ_PLAYER).front());
}

void CSceneSlotMachine::Render(HDC hDC)
{
	
}

void CSceneSlotMachine::Release()
{
    GETSINGLE(CObjMgr)->DeleteLayerObj(OBJ_ROLLING);
}
