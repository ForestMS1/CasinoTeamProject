#include "pch.h"
#include "CRRPlayer.h"

CRRPlayer::CRRPlayer()
{
    m_eRender = GAMEOBJECT;
}

CRRPlayer::~CRRPlayer()
{
    Release();
}

void CRRPlayer::Initialize()
{
    m_tInfo.vPos = { WINCX >> 1, WINCY >> 1 , 0.f };
    m_tInfo.vScale = { 100.f, 200.f, 0.f }; // 세로로 긴 형태

    float fHalfX = m_tInfo.vScale.x * 0.5f;
    float fHalfY = m_tInfo.vScale.y * 0.5f;
}


int CRRPlayer::Update()
{
    return 0;
}

void CRRPlayer::Late_Update()
{
}

void CRRPlayer::Render(HDC hDC)
{
    __super::Draw_Vertex(hDC);
}

void CRRPlayer::Release()
{
}
