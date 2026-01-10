#include "pch.h"
#include "CCointoss.h"

CCointoss::CCointoss()
{
}

CCointoss::~CCointoss()
{
}

void CCointoss::Initialize()
{
  pCoin = new CCoin;
  GETSINGLE(CObjMgr)->AddObject(OBJ_PLAYER, pCoin);
}

int CCointoss::Update()
{
  if (pCoin->Get_isFlip())
  {
    pDuplex = new CDuplex;
    GETSINGLE(CObjMgr)->AddObject(OBJ_PLAYER, pDuplex);
  }
  return OBJ_NOEVENT;
}

void CCointoss::Late_Update()
{
}

void CCointoss::Render(HDC hDC)
{
}

void CCointoss::Release()
{
  GETSINGLE(CObjMgr)->DeleteAllLayer();
}