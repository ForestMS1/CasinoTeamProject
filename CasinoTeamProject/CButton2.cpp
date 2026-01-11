#include "pch.h"
#include "CButton2.h"
#include "CKeyMgr.h"
CButton2::CButton2()
{
  m_eRender = EFFECT;
}

CButton2::~CButton2()
{
}

void CButton2::Initialize()
{
  m_bIsClick = false;

  m_tInfo.vPos = { 550.f, 500.f , 0.f };
  m_tInfo.vScale = { 150.f, 50.f, 0.f };
  m_tInfo.vLook = { 1.f,0.f,0.f };

  float fHalfX = m_tInfo.vScale.x * 0.5f;
  float fHalfY = m_tInfo.vScale.y * 0.5f;

  m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x + fHalfX, m_tInfo.vPos.y - fHalfY, 0.f));
  m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x - fHalfX, m_tInfo.vPos.y - fHalfY, 0.f));
  m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x - fHalfX, m_tInfo.vPos.y + fHalfY, 0.f));
  m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x + fHalfX, m_tInfo.vPos.y + fHalfY, 0.f));

}

int CButton2::Update()
{
  m_tRect.left = m_tInfo.vPos.x - m_tInfo.vScale.x * 0.5f;
  m_tRect.top = m_tInfo.vPos.y - m_tInfo.vScale.y * 0.5f;
  m_tRect.right = m_tInfo.vPos.x + m_tInfo.vScale.x * 0.5f;
  m_tRect.bottom = m_tInfo.vPos.y + m_tInfo.vScale.y * 0.5f;


  if (GETSINGLE(CKeyMgr)->Key_Pressing(VK_LBUTTON))
  {
    POINT ptMouse = { Get_Mouse().x, Get_Mouse().y };
    if (PtInRect(&m_tRect, ptMouse))
    {
      m_bIsClick = true;
    }
  }

    return 0;
}

void CButton2::Late_Update()
{
}

void CButton2::Render(HDC hDC)
{
  LPCSTR ButtonType = "¾Õ";

  if (!m_bIsClick)
  {
    __super::Draw_Vertex_Color(hDC, 0, 0, 0);
    TextOutA(hDC, m_tRect.left, m_tRect.top, ButtonType, lstrlenA(ButtonType));
  }
  else
  {
    __super::Draw_Vertex_Color(hDC, 255, 0, 0);
    TextOutA(hDC, m_tRect.left, m_tRect.top, ButtonType, lstrlenA(ButtonType));
  }
}

void CButton2::Release()
{
}
