#include "pch.h"
#include "CBullet.h"

CBullet::CBullet()
{
    m_eRender = GAMEOBJECT;
    D3DXMatrixIdentity(&m_matRotate);
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
    // 총알은 권총보다 작게 설정 (예: 30x15)
    //m_tInfo.vPos = { (WINCX >> 1), (WINCY >> 1) + 200.f, 0.f };
    m_tInfo.vScale = { 30.f, 15.f, 0.f };

    float fHalfX = m_tInfo.vScale.x * 0.5f;
    float fHalfY = m_tInfo.vScale.y * 0.5f;

#pragma region 총알 실루엣 좌표
    // 1. 탄두 끝 (오른쪽 중심)
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x + fHalfX, m_tInfo.vPos.y, 0.f));

    // 2. 탄두 상단 어깨 (탄두가 둥글게 꺾이는 지점)
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x + fHalfX * 0.3f, m_tInfo.vPos.y - fHalfY, 0.f));

    // 3. 탄피 상단 뒷부분 (왼쪽 위)
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x - fHalfX, m_tInfo.vPos.y - fHalfY, 0.f));

    // 4. 탄피 하단 뒷부분 (왼쪽 아래)
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x - fHalfX, m_tInfo.vPos.y + fHalfY, 0.f));

    // 5. 탄두 하단 어깨 (탄두가 시작되는 지점)
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x + fHalfX * 0.3f, m_tInfo.vPos.y + fHalfY, 0.f));
#pragma endregion

    m_fSpeed = 5.f;

    D3DXMATRIX matGoOriginTrans, matGoPrev;
    D3DXMatrixIdentity(&matGoOriginTrans);
    D3DXMatrixIdentity(&matGoPrev);

    // 원점으로 이동하는 행렬
    D3DXMatrixTranslation(&matGoOriginTrans, -m_tInfo.vPos.x, -m_tInfo.vPos.y, -m_tInfo.vPos.z);
    // 제자리로 이동하는 행렬
    D3DXMatrixTranslation(&matGoPrev, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

    // 총이 발사될 때 총의 회전정도를 총알에 적용
    for (auto& vertex : m_vVertexes)
    {
        D3DXVec3TransformCoord(&vertex, &vertex, &matGoOriginTrans);
        D3DXVec3TransformCoord(&vertex, &vertex, &m_matRotate);
        D3DXVec3TransformCoord(&vertex, &vertex, &matGoPrev);
    }
}

int CBullet::Update()
{
    D3DXMATRIX matTrans;
    D3DXMatrixTranslation(&matTrans, m_tInfo.vDir.x * m_fSpeed, m_tInfo.vDir.y * m_fSpeed, m_tInfo.vDir.z * m_fSpeed);
    m_tInfo.matWorld = matTrans;
    for (auto& vertex : m_vVertexes)
    {
        D3DXVec3TransformCoord(&vertex, &vertex, &m_tInfo.matWorld);
    }

	return 0;
}

void CBullet::Late_Update()
{
}

void CBullet::Render(HDC hDC)
{
    __super::Draw_Vertex(hDC);
}

void CBullet::Release()
{
}
