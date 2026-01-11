#include "pch.h"
#include "CCoin.h"

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

  m_bArrive = false;
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

  if (!m_bArrive)
  {
    if (GetAsyncKeyState(VK_SPACE))
    {
      if (m_tInfo.vPos.y > 100 && m_bisTop == false)
      {
        m_tInfo.vPos.y -= m_fSpeed;
        m_fAngle += D3DXToRadian(5.f);
      }
      else
        m_bisTop = true;

      if (m_tInfo.vPos.y < 450 && m_bisTop == true)
      {
        m_tInfo.vPos.y += m_fSpeed;
        m_fAngle += D3DXToRadian(5.f);
      }
      if (m_tInfo.vPos.y >= 450 && m_bisTop == true)
      {
        m_fAngle = 33.f;
        m_bisTop = false;
        m_bArrive = true;
      }
    }
  }

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
}

void CCoin::Release()
{
}