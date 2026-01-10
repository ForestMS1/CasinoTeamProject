#include "pch.h"
#include "CRevolver.h"
#include "CObjMgr.h"
#include "CBullet.h"
#include "CKeyMgr.h"
#include "CShotEventObserver.h"

CRevolver::CRevolver() : 
    m_iProbability(0),
    m_fAngle(2.f),
    m_bIsRight(true),
    m_bIsShotInit(false)
{
	m_eRender = GAMEOBJECT;
    D3DXMatrixIdentity(&m_matRotate);
}

CRevolver::~CRevolver()
{
	Release();
}

void CRevolver::Initialize()
{
    m_tInfo.vPos = { WINCX >> 1, WINCY >> 1 , 0.f };
    m_tInfo.vDir = { 1.f, 0.f, 0.f };
    m_tInfo.vScale = { 200.f, 200.f, 0.f };

    float fHalfX = m_tInfo.vScale.x * 0.5f;
    float fHalfY = m_tInfo.vScale.y * 0.5f;

#pragma region 권총 실루엣 좌표
    // 1. 총구 상단 (오른쪽 끝)
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x + fHalfX, m_tInfo.vPos.y - 20.f, 0.f));

    // 2. 총열 및 몸체 상단 (왼쪽으로 이동)
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x - 30.f, m_tInfo.vPos.y - 20.f, 0.f));

    // 3. 해머/뒷부분 곡선 (뒷부분 상단)
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x - 60.f, m_tInfo.vPos.y - 40.f, 0.f));

    // 4. 손잡이 뒷면 끝 (가장 왼쪽 아래)
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x - 90.f, m_tInfo.vPos.y + fHalfY, 0.f));

    // 5. 손잡이 밑면 (오른쪽으로 살짝 이동)
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x - 40.f, m_tInfo.vPos.y + fHalfY, 0.f));

    // 6. 손잡이 앞면 및 방아쇠 울 뒷부분
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x - 20.f, m_tInfo.vPos.y + 30.f, 0.f));

    // 7. 방아쇠 울 및 실린더 하단 (앞쪽)
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x + 30.f, m_tInfo.vPos.y + 30.f, 0.f));

    // 8. 총열 하단 (총구 아래쪽)
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x + fHalfX, m_tInfo.vPos.y + 10.f, 0.f));
#pragma endregion

    m_vecMuzzle = { m_tInfo.vPos.x + fHalfX, m_tInfo.vPos.y - 20.f, 0.f };

    srand(time(NULL));
}

int CRevolver::Update()
{
    if (GETSINGLE(CKeyMgr)->Key_Down('C'))
    {
        m_iProbability = (rand() % 6) + 1; // 1~6
        m_bIsShotInit = true;
        Shot();
        m_bIsRight = !m_bIsRight;
    }
	return 0;
}

void CRevolver::Late_Update()
{
    if (m_bIsShotInit == false)
        return; // 처음 회전 방지
    Rotate_Muzzle();
}

void CRevolver::Render(HDC hDC)
{
    __super::Draw_Vertex(hDC);
}

void CRevolver::Release()
{

}

void CRevolver::Rotate_Muzzle()
{
    if (m_fAngle > 180.f && m_bIsRight == true)
        return;
    if (m_fAngle < 0.f && m_bIsRight == false)
        return;
    if (m_iProbability == 6)
        return;

    D3DXMATRIX matGoOriginTrans, matGoPrev;
    D3DXMatrixIdentity(&m_matRotate);
    D3DXMatrixIdentity(&matGoOriginTrans);
    D3DXMatrixIdentity(&matGoPrev);


    // 원점으로 이동하는 행렬
    D3DXMatrixTranslation(&matGoOriginTrans, -m_tInfo.vPos.x, -m_tInfo.vPos.y, -m_tInfo.vPos.z);
    // 회전행렬
    if (m_bIsRight)
    {
        m_fAngle += 1.f;
        D3DXMatrixRotationY(&m_matRotate, D3DXToRadian(1));
    }
    else
    {
        m_fAngle -= 1.f;
        D3DXMatrixRotationY(&m_matRotate, D3DXToRadian(-1));
    }
    // 제자리로 이동하는 행렬
    D3DXMatrixTranslation(&matGoPrev, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

    // 총 몸체 돌림
    for (auto& vertex : m_vVertexes)
    {
        D3DXVec3TransformCoord(&vertex, &vertex, &matGoOriginTrans);
        D3DXVec3TransformCoord(&vertex, &vertex, &m_matRotate);
        D3DXVec3TransformCoord(&vertex, &vertex, &matGoPrev);
    }

    // 총알 나가는 총구도 돌림
    D3DXVec3TransformCoord(&m_vecMuzzle, &m_vecMuzzle, &matGoOriginTrans);
    D3DXVec3TransformCoord(&m_vecMuzzle, &m_vecMuzzle, &m_matRotate);
    D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &m_matRotate);
    D3DXVec3TransformCoord(&m_vecMuzzle, &m_vecMuzzle, &matGoPrev);
}

void CRevolver::Shot()
{
    // 리볼버 돌리고 다시
    if (m_iProbability != 6)
    {
        GETSINGLE(CShotEventObserver)->Set_Shot(true);
        return;
    }
    // 실제 총알 발사
    else
    {
        CBullet* pBullet = new CBullet;
        pBullet->Set_Dir(m_tInfo.vDir);
        pBullet->Set_Pos(m_vecMuzzle);
        D3DXMatrixRotationY(&m_matRotate, D3DXToRadian(m_fAngle));
        pBullet->Set_MatRotate(m_matRotate);
        pBullet->Initialize();
        GETSINGLE(CObjMgr)->AddObject(OBJ_ITEM, pBullet);
    }
}
