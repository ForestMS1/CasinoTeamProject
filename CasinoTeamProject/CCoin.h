#pragma once
#include "CObj.h"
class CCoin :  public CObj
{
public:
  CCoin();
  ~CCoin();
public:
  // CObj을(를) 통해 상속됨
  void Initialize() override;
  int Update() override;
  void Late_Update() override;
  void Render(HDC hDC) override;
  void Release() override;

private:
  float m_fAngle;
  D3DXVECTOR3 vLocal[4];
  POINT tPoints[4];

};

