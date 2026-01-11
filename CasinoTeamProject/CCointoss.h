#pragma once
#include "CScene.h"
#include "CCoin.h"
#include "CDuplex.h"
#include "CButton.h"
#include "CButton2.h"

class CCointoss : public CScene
{
public:
  CCointoss();
  virtual ~CCointoss();
public:
  // CScene을(를) 통해 상속됨
  void Initialize() override;
  int Update() override;
  void Late_Update() override;
  void Render(HDC hDC) override;
  void Release() override;
  void Key_Input();

private:
  bool   m_isDead;

  CButton2* pButton2;
  CButton* pButton;
  CCoin*   pCoin;
  CDuplex* pDuplex;
};

