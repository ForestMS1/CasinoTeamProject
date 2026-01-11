#include "pch.h"
#include "CCointoss.h"

CCointoss::CCointoss() 
  : m_isDead(false)
, pButton2  (nullptr)
, pButton   (nullptr)
, pCoin     (nullptr)
{
}

CCointoss::~CCointoss()
{
}

void CCointoss::Initialize()
{
  pCoin = new CCoin;
  GETSINGLE(CObjMgr)->AddObject(OBJ_PLAYER, pCoin);

  pButton = new CButton;
  GETSINGLE(CObjMgr)->AddObject(OBJ_EFFECT, pButton);

  pButton2 = new CButton2;
  GETSINGLE(CObjMgr)->AddObject(OBJ_EFFECT, pButton2);

  __super::Initialize();
  GETSINGLE(CObjMgr)->Initialize();
}

int CCointoss::Update()
{

  float Angle = 33.f;
  
  if (pCoin->Get_Arrive())
    pCoin->Set_Angle(Angle);

  if (pButton->Get_Clicked())
  {
    Angle = 38.f;
    pCoin->Set_Angle(Angle);
  }
  else if (pButton2->Get_Clicked())
  {
    Angle = 38.f;
    pCoin->Set_Angle(Angle);
  }

  return 0;
}

void CCointoss::Late_Update()
{
    __super::Late_Update();
}

void CCointoss::Render(HDC hDC)
{
  //if (pButton->Get_Clicked())
  //{
  //  pCoin->Print_Text(hDC);
  //}
  //if (pButton2->Get_Clicked())
  //{
  //  pCoin->Print_Text(hDC);
  //}
}

void CCointoss::Release()
{
  GETSINGLE(CObjMgr)->DeleteAllLayer();
}