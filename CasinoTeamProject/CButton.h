#pragma once
#include "CObj.h"
class CButton : public CObj
{
public:
  CButton();
  virtual ~CButton();
public:
  // CObj을(를) 통해 상속됨
  void Initialize() override;
  int Update() override;
  void Late_Update() override;
  void Render(HDC hDC) override;
  void Release() override;
private:
  RECT        m_tRect;
  bool        m_bIsClick;

};

