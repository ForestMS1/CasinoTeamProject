#pragma once
#include "CScene.h"
#include "CDuplex.h"
#include "CCoin.h"
class CCointoss : public CScene
{
public:
  CCointoss();
  ~CCointoss();
public:
  // CScene을(를) 통해 상속됨
  void Initialize() override;
  int Update() override;
  void Late_Update() override;
  void Render(HDC hDC) override;
  void Release() override;
private:
  CDuplex* pDuplex;
  CCoin*   pCoin;
};

