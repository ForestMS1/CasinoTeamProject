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

  CCoin* pCoin = new CCoin;
  GETSINGLE(CObjMgr)->AddObject(OBJ_PLAYER, pCoin);

  CButton* pButton = new CButton;
  GETSINGLE(CObjMgr)->AddObject(OBJ_EFFECT, pButton);

  CButton2* pButton2 = new CButton2;
  GETSINGLE(CObjMgr)->AddObject(OBJ_EFFECT, pButton2);

}

int CCointoss::Update()
{
  //if (pCoin->Get_Arrive())
  //{
  //}
  //CDuplex* pDuplex = new CDuplex;
  //GETSINGLE(CObjMgr)->AddObject(OBJ_PLAYER, pDuplex);

  return 0;
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