#include "pch.h"
#include "CCointoss.h"
#include "CCoin.h"

CCointoss::CCointoss()
{
}

CCointoss::~CCointoss()
{
}

void CCointoss::Initialize()
{
  CCoin* testCoin = new CCoin;
  GETSINGLE(CObjMgr)->AddObject(OBJ_PLAYER, testCoin);
}

int CCointoss::Update()
{
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