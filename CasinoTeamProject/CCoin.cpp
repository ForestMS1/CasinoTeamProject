#include "pch.h"
#include "CCoin.h"
#include "CObjMgr.h"
#include "CButton.h"
#include "CButton2.h"
CCoin::CCoin():m_fAngle(0.f),m_bisTop(false)
{
  m_eRender = PLAYER;
  m_fSpeed = 10.f;
}

CCoin::~CCoin()
{
}

void CCoin::Initialize()
{
  vLocal.resize(SEGMENT);  
  
  srand((int)time(NULL));
  int num = rand() % 3 + 1;

  m_bArrive = false;
  m_bisTop = false;

  m_tInfo.vPos = { 400.f,400.f,0 };
  m_tInfo.vDir = { 1.f,0.f,0.f };


  for (int i = 0; i < SEGMENT; ++i)
  {
      float theta = (2.f * D3DX_PI / SEGMENT) * i;
      vLocal[i].x = cosf(theta) * 25.f;
      vLocal[i].y = sinf(theta) * 25.f;
      vLocal[i].z = 0.f;
  }

  for (int i = 0; i < SEGMENT; ++i)
  {
      D3DXVec3TransformCoord(&vWorld, &vLocal[i], &m_tInfo.matWorld);
      tPoints[i].x = (LONG)(vWorld.x);
      tPoints[i].y = (LONG)(vWorld.y);
  }
}

int CCoin::Update()
{
  m_isMove = false;

  srand((int)time(NULL));
  int num = rand() % 3 + 1;

  D3DXMATRIX matScale, matRotZ, matTrans;

  D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
  D3DXMatrixRotationX(&matRotZ, m_fAngle);
  D3DXMatrixTranslation(&matTrans, 
    m_tInfo.vPos.x,
    m_tInfo.vPos.y,
    m_tInfo.vPos.z
  );

  m_tInfo.matWorld = matScale * matRotZ * matTrans;

  if (!m_bArrive)
  {
    if (GetAsyncKeyState(VK_SPACE))
    {
      if (m_tInfo.vPos.y > 100 && m_bisTop == false)
      {
        m_tInfo.vPos.y -= m_fSpeed;
        m_fAngle += D3DXToRadian(7.f);
      }
      else
        m_bisTop = true;

      if (m_tInfo.vPos.y < 400 && m_bisTop == true)
      {
        m_tInfo.vPos.y += m_fSpeed;
        m_fAngle += D3DXToRadian(7.f);
      }
      if (m_tInfo.vPos.y >= 400 && m_bisTop == true)
      {
        m_fAngle = 33.f;
        m_bisTop = false;
        m_bArrive = true;
      }
    }
  }
  
  if (num == FRONT)
    FB = FRONT;
  else
    FB = BACK;

  return 0;
}

void CCoin::Late_Update()
{
  for (int i = 0; i < SEGMENT; ++i)
  {
    float theta = (2.f * D3DX_PI / SEGMENT) * i;
    vLocal[i].x = cosf(theta) * 25.f;
    vLocal[i].y = sinf(theta) * 25.f;
    vLocal[i].z = 0.f;
  }

  for (int i = 0; i < SEGMENT; ++i)
  {
    D3DXVec3TransformCoord(&vWorld, &vLocal[i], &m_tInfo.matWorld);
    tPoints[i].x = (LONG)(vWorld.x);
    tPoints[i].y = (LONG)(vWorld.y);
  }
}

void CCoin::Render(HDC hDC)
{
  Polygon(hDC, tPoints, SEGMENT);

  if (dynamic_cast<CButton*>(GETSINGLE(CObjMgr)->GetObjLayer(OBJ_EFFECT).front())->Get_Clicked())
  {
    Print_Text(hDC);
  }
  if (dynamic_cast<CButton2*>(GETSINGLE(CObjMgr)->GetObjLayer(OBJ_EFFECT).back())->Get_Clicked())
  {
    Print_Text(hDC);
  }
}

void CCoin::Release()
{
}

void CCoin::Print_Text(HDC hDC)
{
  LPCSTR FrontBack ="";
  

  if (FB == FRONT)
  {

    FrontBack = "back";
    Draw_Vertex_Color(hDC, 255, 0, 0);
    TextOutA(hDC, (int)m_tInfo.vPos.x-15, (int)m_tInfo.vPos.y-15, FrontBack, lstrlenA(FrontBack));
  }
  if (FB == BACK)
  {

    FrontBack = "front";
    Draw_Vertex_Color(hDC, 255, 0, 0);
    TextOutA(hDC, (int)m_tInfo.vPos.x -15, (int)m_tInfo.vPos.y -15, FrontBack, lstrlenA(FrontBack));
  }
}
