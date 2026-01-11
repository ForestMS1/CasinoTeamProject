#pragma once
#include "CObj.h"
class CCoin :  public CObj
{
public:
  CCoin();

  virtual ~CCoin();

public:
  // CObjÀ»(¸¦) ÅëÇØ »ó¼ÓµÊ
  void Initialize() override;
  int Update() override;
  void Late_Update() override;
  void Render(HDC hDC) override;
  void Release() override;

  bool Get_Arrive() { return m_bArrive; }

private:
  float m_fAngle;
  bool  m_isMove;
  bool  m_bisTop;
  bool  m_bArrive;

  const int SEGMENT = 32;

  vector<D3DXVECTOR3> vLocal;
  D3DXVECTOR3 vWorld;

  POINT tPoints[32];
  POINT m_SawPoints[6] ;
};

