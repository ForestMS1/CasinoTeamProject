#include "pch.h"
#include "CCoin.h"

CCoin::CCoin():m_fAngle(0.f)
{
  m_eRender = PLAYER;
}

CCoin::~CCoin()
{
}

void CCoin::Initialize()
{
  m_tInfo.vPos = { 400,300,0 };
  m_tInfo.vDir = { 1.f,0.f,0.f };
}

int CCoin::Update()
{
  D3DXMATRIX matScale, matRotx, matTrans;

  D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
  D3DXMatrixRotationZ(&matRotx, m_fAngle);
  D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x,
    m_tInfo.vPos.y,
    m_tInfo.vPos.z);

  m_tInfo.matWorld = matScale * matRotx * matTrans;

  m_fAngle += D3DXToRadian(30.f);

  return 0;
}

void CCoin::Late_Update()
{
}

void CCoin::Render(HDC hDC)
{
    float fHalfWidth = 50.f;
    float fHalfHeight = 8.f;
  
    D3DXVECTOR3 vLocal[4] = {
      D3DXVECTOR3(-fHalfWidth, -fHalfHeight, 0.f),
      D3DXVECTOR3(fHalfWidth, -fHalfHeight, 0.f),
      D3DXVECTOR3(fHalfWidth,  fHalfHeight, 0.f),
      D3DXVECTOR3(-fHalfWidth,  fHalfHeight, 0.f)
    };
  
    // 월드 변환을 적용한 화면 좌표 계산

    for (int i = 0; i < 4; ++i)
    {
      D3DXVECTOR3 vWorld;
      D3DXVec3TransformCoord(&vWorld, &vLocal[i], &m_tInfo.matWorld);
      tPoints[i].x = (LONG)(vWorld.x);
      tPoints[i].y = (LONG)(vWorld.y);
    }
  
    // 외곽선 그리기
    Polygon(hDC, tPoints, 4);
  
    // 옆면 톱니 무늬 그리기 (변형된 좌표 사용)
    int iGap = 8;
    for (LONG x = tPoints[0].x + iGap; x < tPoints[1].x; x += iGap)
    {
      MoveToEx(hDC, x, tPoints[0].y, nullptr);
      LineTo(hDC, x, tPoints[3].y);
    }
}

void CCoin::Release()
{
}