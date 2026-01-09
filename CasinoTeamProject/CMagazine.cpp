#include "pch.h"
#include "CMagazine.h"
#include "CKeyMgr.h"
CMagazine::CMagazine()
    :m_fAngle(0.f)
{
    m_eRender = GAMEOBJECT;
}

CMagazine::~CMagazine()
{
	Release();
}

void CMagazine::Initialize()
{
    m_tInfo.vPos = { WINCX - 100.f, WINCY - 100.f, 0.f };
    m_tInfo.vScale = { 100.f, 100.f, 0.f };

    float fOuterRadius = m_tInfo.vScale.x * 0.5f;    // 전체 탄창 반지름
    float fInnerRadius = fOuterRadius * 0.3f;      // 총알 구멍 반지름
    float fOffset = fOuterRadius * 0.6f;           // 중심에서 구멍까지의 거리

#pragma region 탄창 외곽선 (큰 원)
    for (int i = 0; i <= 20; ++i) // 20개의 점으로 원 표현
    {
        float fAngle = D3DXToRadian(i * (360.f / 20.f));
        m_vVertexes.push_back(D3DXVECTOR3(
            m_tInfo.vPos.x + cosf(fAngle) * fOuterRadius,
            m_tInfo.vPos.y + sinf(fAngle) * fOuterRadius,
            0.f));
    }
#pragma endregion

#pragma region 탄창 구멍 (6개)
    // 60도 간격으로 6개의 구멍 위치 설정
    for (int i = 0; i < 6; ++i)
    {
        float fCenterAngle = D3DXToRadian(i * 60.f);
        float fCenterX = m_tInfo.vPos.x + cosf(fCenterAngle) * fOffset;
        float fCenterY = m_tInfo.vPos.y + sinf(fCenterAngle) * fOffset;

        // 각 구멍의 원 그리기 (간단하게 8각형으로 표현)
        for (int j = 0; j <= 8; ++j)
        {
            float fHoleAngle = D3DXToRadian(j * (360.f / 8.f));
            m_vVertexes.push_back(D3DXVECTOR3(
                fCenterX + cosf(fHoleAngle) * fInnerRadius,
                fCenterY + sinf(fHoleAngle) * fInnerRadius,
                0.f));
        }

        // 주의: Line Strip 사용 시 구멍들 사이가 선으로 이어질 수 있습니다.
        // 이 경우 구멍 하나를 다 그릴 때마다 DrawIndexedPrimitive 등으로 끊어서 그려야 합니다.
    }
#pragma endregion
}

int CMagazine::Update()
{
    
    Rotate();
	
    return 0;
}

void CMagazine::Late_Update()
{
}

void CMagazine::Render(HDC hDC)
{
	__super::Draw_Vertex(hDC);
}

void CMagazine::Release()
{
}

void CMagazine::Rotate()
{
    if (m_fAngle > 180.f)
        return;
    D3DXMATRIX matRotate, matGoOriginTrans, matGoPrevTrans;
    D3DXMatrixIdentity(&matRotate);
    D3DXMatrixIdentity(&matGoOriginTrans);
    D3DXMatrixIdentity(&matGoPrevTrans);

    D3DXMatrixTranslation(&matGoOriginTrans, -m_tInfo.vPos.x, -m_tInfo.vPos.y, -m_tInfo.vPos.z);
    m_fAngle += 5.f;
    D3DXMatrixRotationZ(&matRotate, D3DXToRadian(5.f));
    D3DXMatrixTranslation(&matGoPrevTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

    for (auto& vertex : m_vVertexes)
    {
        D3DXVec3TransformCoord(&vertex, &vertex, &matGoOriginTrans);
        D3DXVec3TransformCoord(&vertex, &vertex, &matRotate);
        D3DXVec3TransformCoord(&vertex, &vertex, &matGoPrevTrans);
    }
}
