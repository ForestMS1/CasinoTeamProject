#pragma once
#include "CObj.h"
class CButton2 : public CObj
{
public:
  CButton2();
  virtual ~CButton2();
  // CObj을(를) 통해 상속됨
public:
  void Initialize() override;
  int Update() override;
  void Late_Update() override;
  void Render(HDC hDC) override;
  void Release() override;
  bool Get_Clicked() { return m_bIsClick; }

private:
  RECT        m_tRect;
  bool        m_bIsClick;
};

