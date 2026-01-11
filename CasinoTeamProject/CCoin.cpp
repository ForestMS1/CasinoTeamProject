#include "pch.h"
#include "CCoin.h"

CCoin::CCoin():m_fAngle(0.f),m_bisTop(false)
{
  m_eRender = PLAYER;
  m_fSpeed = 3.f;
}

CCoin::~CCoin()
{
}

void CCoin::Initialize()
{
  vLocal.resize(SEGMENT);

  m_bisTop = false;
  m_tInfo.vPos = { 400.f,450.f,0 };
  m_tInfo.vDir = { 1.f,0.f,0.f };
}

int CCoin::Update()
{
  m_isMove = false;
  D3DXMATRIX matScale, matRotX, matTrans;

  D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
  D3DXMatrixRotationX(&matRotX, m_fAngle);
  D3DXMatrixTranslation(&matTrans, 
    m_tInfo.vPos.x,
    m_tInfo.vPos.y,
    m_tInfo.vPos.z);

  m_tInfo.matWorld = matScale * matRotX * matTrans;

  if (GetAsyncKeyState(VK_SPACE))
  {
    if (m_tInfo.vPos.y > 100 && m_bisTop == false)
      m_tInfo.vPos.y -= m_fSpeed;
    else
      m_bisTop = true;

    if (m_tInfo.vPos.y < 450 && m_bisTop == true)
      m_tInfo.vPos.y += m_fSpeed;
    if (m_tInfo.vPos.y >= 450 && m_bisTop == true)
    { 
      m_fAngle = 0.f;
      m_bisTop = false;
      m_bArrive = true;
    }
  }
  
  if (GetAsyncKeyState(VK_RIGHT))
    m_fAngle += D3DXToRadian(3.f);

  if (GetAsyncKeyState(VK_LEFT))
    m_fAngle -= D3DXToRadian(3.f);

  return 0;
}

void CCoin::Late_Update()
{
}

void CCoin::Render(HDC hDC)
{
  // 동전 크기 설정 (로컬 공간)
   // float fHalfWidth = 50.f;
   // float fHalfHeight = 8.f;
   //
   // // 로컬 공간의 4개 꼭짓점 (사각형 찍을 떄 사용하는 점들)
   // D3DXVECTOR3 vLocal[4] = {
   //   D3DXVECTOR3(-fHalfWidth, -fHalfHeight, 0.f),
   //   D3DXVECTOR3(fHalfWidth, -fHalfHeight, 0.f),
   //   D3DXVECTOR3(fHalfWidth,  fHalfHeight, 0.f),
   //   D3DXVECTOR3(-fHalfWidth,  fHalfHeight, 0.f)
   // };
   //
   // for (int i = 0; i < 4; ++i)
   // {
   //   D3DXVec3TransformCoord(&vWorld, &vLocal[i], &m_tInfo.matWorld);
   //   tPoints[i].x = (LONG)(vWorld.x);
   //   tPoints[i].y = (LONG)(vWorld.y);
   // }  
   //
   // Polygon(hDC, tPoints, 4);

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

    Polygon(hDC, tPoints, 32);

    
 // int iGap = 8;
 //
 // // tPoints[0].x (왼쪽 끝) 부터 tPoints[1].x (오른쪽 끝) 까지 반복
 // for (LONG x = tPoints[0].x + iGap; x < tPoints[1].x; x += iGap)
 // {
 //   // 위쪽 y좌표(tPoints[0].y)에서 아래쪽 y좌표(tPoints[3].y)로 선 긋기
 //   MoveToEx(hDC, x, tPoints[0].y, nullptr);
 //   LineTo(hDC, x, tPoints[3].y);
 // }
}

void CCoin::Release()
{
}