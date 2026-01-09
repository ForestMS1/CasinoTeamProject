#include "pch.h"
#include "CCard.h"

CCard::CCard() 
    : m_bIsOpen(false),
    m_iIndex(0),
    m_eType(TYPE_END)
{
    m_eRender = GAMEOBJECT;
}

CCard::~CCard()
{
    Release();
}

void CCard::Initialize()
{
    m_tInfo.vScale = { 75.f, 100.f, 0.f };
    float fHalfX = m_tInfo.vScale.x * 0.5f;
    float fHalfY = m_tInfo.vScale.y * 0.5f;

#pragma region Ä«µå Á¡Âï±â
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x + fHalfX, m_tInfo.vPos.y - fHalfY, 0.f));
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x - fHalfX, m_tInfo.vPos.y - fHalfY, 0.f));
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x - fHalfX, m_tInfo.vPos.y + fHalfY, 0.f));
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x + fHalfX, m_tInfo.vPos.y + fHalfY, 0.f));
#pragma endregion
}

int CCard::Update()
{
    return 0;
}

void CCard::Late_Update()
{
}

void CCard::Render(HDC hDC)
{
    __super::Draw_Vertex(hDC);
}

void CCard::Release()
{
}
