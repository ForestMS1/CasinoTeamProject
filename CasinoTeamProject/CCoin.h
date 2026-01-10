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
  bool  m_isMove;
  bool  m_bisTop;

  D3DXVECTOR3 vLocal[4];
  D3DXVECTOR3 vWorld;

  POINT tPoints[4];
  POINT m_SawPoints[6] ;
};

