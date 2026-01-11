#pragma once
#include "CObj.h"
#include "time.h"
class CCoin :  public CObj
{
public:
  CCoin();
  virtual ~CCoin();
  enum FRONTBACK { FB_START, FRONT, BACK, FB_END };
public:
  void Initialize() override;
  int Update() override;
  void Late_Update() override;
  void Render(HDC hDC) override;
  void Release() override;
  
  void  Set_Angle  (float fAngle) { m_fAngle = fAngle; }
  bool  Get_Arrive ()             { return m_bArrive; }
  void  Print_Text(HDC hDC);
private:
  float m_fAngle;
  bool  m_isMove;
  bool  m_bisTop;
  bool  m_bArrive;

  const int SEGMENT = 32;

  vector<D3DXVECTOR3> vLocal;
  D3DXVECTOR3 vWorld;


  RECT        m_tRect;
  FRONTBACK FB;
  POINT tPoints[32];
  POINT m_SawPoints[6] ;
};

