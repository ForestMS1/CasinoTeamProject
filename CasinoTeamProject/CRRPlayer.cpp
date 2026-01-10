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
    //m_tInfo.vPos = { WINCX >> 1, WINCY >> 1 , 0.f };
    m_tInfo.vScale = { 100.f, 200.f, 0.f }; // 세로로 긴 형태

    float fHalfX = m_tInfo.vScale.x * 0.5f;
    float fHalfY = m_tInfo.vScale.y * 0.5f;

#pragma region 졸라맨 좌표 (Line Strip 기준)
    // --- 머리 (간단하게 다이아몬드 형태) ---
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y - fHalfY, 0.f));          // 머리 꼭대기
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x - 20.f, m_tInfo.vPos.y - fHalfY + 20.f, 0.f)); // 머리 왼쪽
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y - fHalfY + 40.f, 0.f));    // 목/머리 아래
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x + 20.f, m_tInfo.vPos.y - fHalfY + 20.f, 0.f)); // 머리 오른쪽
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y - fHalfY, 0.f));          // 다시 머리 위 (연결)

    // --- 몸통 ---
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y - fHalfY + 40.f, 0.f));    // 목으로 이동
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y + 20.f, 0.f));             // 골반까지

    // --- 다리 ---
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x - 30.f, m_tInfo.vPos.y + fHalfY, 0.f));    // 왼발 끝
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y + 20.f, 0.f));             // 다시 골반
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x + 30.f, m_tInfo.vPos.y + fHalfY, 0.f));    // 오른발 끝

    // --- 팔 (어깨 지점으로 이동 후 그리기) ---
    // 주의: Line Strip 사용 시 선이 겹칠 수 있으므로, 렌더링 방식에 따라 조정이 필요할 수 있습니다.
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y - 20.f, 0.f));             // 어깨 위치
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x - 40.f, m_tInfo.vPos.y + 10.f, 0.f));    // 왼손 끝
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y - 20.f, 0.f));             // 다시 어깨
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x + 40.f, m_tInfo.vPos.y + 10.f, 0.f));    // 오른손 끝
#pragma endregion
}


int CRRPlayer::Update()
{
    if (m_bIsDead)
        return OBJ_DEAD;
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
