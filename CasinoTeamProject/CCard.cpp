#include "pch.h"
#include "CCard.h"
#include "CCardMgr.h"
#include "CKeyMgr.h"
int CCard::_sCardCnt = 0;

CCard::CCard()
    : m_bIsOpen(false),
    m_eType(TYPE_END),
    m_bFlipComplete(false),
    m_fFlipAngle(0.f)
{
    m_eRender = GAMEOBJECT;
    _sCardCnt++;
    m_iIndex = _sCardCnt-1;
}

CCard::CCard(CARDTYPE _type)
    : m_bIsOpen(false),
    m_bFlipComplete(false),
    m_fFlipAngle(0.f)
{
    m_eRender = GAMEOBJECT;
    _sCardCnt++;
    m_iIndex = _sCardCnt - 1;
    m_eType = _type;
}

CCard::~CCard()
{
    Release();
}

void CCard::Initialize()
{
    m_tInfo.vScale = { 75.f, 100.f, 0.f };
    m_tInfo.vLook = { 0.f, 1.f, 0.f };
    float fHalfX = m_tInfo.vScale.x * 0.5f;
    float fHalfY = m_tInfo.vScale.y * 0.5f;

#pragma region 카드 점찍기
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x + fHalfX, m_tInfo.vPos.y - fHalfY, 0.f));
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x - fHalfX, m_tInfo.vPos.y - fHalfY, 0.f));
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x - fHalfX, m_tInfo.vPos.y + fHalfY, 0.f));
    m_vVertexes.push_back(D3DXVECTOR3(m_tInfo.vPos.x + fHalfX, m_tInfo.vPos.y + fHalfY, 0.f));
#pragma endregion
    m_dvPos = GETSINGLE(CCardMgr)->Get_CardPos(m_iIndex);
    m_fSpeed = 5.f;
}

int CCard::Update()
{
#pragma region 카드 배치
    // 현재 위치에서 목적지로 향하는 벡터 구하기
    D3DXVECTOR3 dvTarget = m_dvPos - m_tInfo.vPos;

    // 정해진 위치까지 카드 이동
    if (D3DXVec3Length(&dvTarget) > 5.f)
    {
        D3DXMATRIX matScale, matRotate, matTrans;
        D3DXMatrixIdentity(&matScale);
        D3DXMatrixIdentity(&matRotate);
        D3DXMatrixIdentity(&matTrans);


        // 회전행렬 구하기
        D3DXMatrixRotationZ(&matRotate, D3DXToRadian(5.f));


        // 이동행렬 구하기
        D3DXVec3Normalize(&dvTarget, &dvTarget);
        dvTarget *= m_fSpeed;
        D3DXMatrixTranslation(&matTrans, dvTarget.x, dvTarget.y, dvTarget.z);

        

        // 원점으로 이동하는 행렬, 원래 자리로 돌아오는 행렬 구하기
        D3DXMATRIX matGoOrigin, matGoPrev;
        D3DXMatrixIdentity(&matGoOrigin);
        D3DXMatrixIdentity(&matGoPrev);
        D3DXMatrixTranslation(&matGoOrigin, -m_tInfo.vPos.x, -m_tInfo.vPos.y, -m_tInfo.vPos.z);
        D3DXMatrixTranslation(&matGoPrev, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);


        for (auto& vertex : m_vVertexes)
        {
            //회전
            D3DXVec3TransformCoord(&vertex, &vertex, &matGoOrigin);
            D3DXVec3TransformCoord(&vertex, &vertex, &matRotate);
            D3DXVec3TransformCoord(&vertex, &vertex, &matGoPrev);

            // 이동
            D3DXVec3TransformCoord(&vertex, &vertex, &matTrans);
        }
        D3DXVec3TransformCoord(&m_tInfo.vLook, &m_tInfo.vLook, &matRotate);
        D3DXVec3TransformCoord(&m_tInfo.vPos, &m_tInfo.vPos, &matTrans);
    }
    else
    {
        D3DXVECTOR3 axisY = { 0.f, 1.f, 0.f };
        float dot = D3DXVec3Dot(&m_tInfo.vLook, &axisY);
        float angle = acosf(dot);
        if (D3DXToDegree(angle) > 1.f)
        {
            D3DXMATRIX matRotate;
            D3DXMatrixIdentity(&matRotate);


            // 회전행렬 구하기
            D3DXMatrixRotationZ(&matRotate, D3DXToRadian(5.f));

            // 원점으로 이동하는 행렬, 원래 자리로 돌아오는 행렬 구하기
            D3DXMATRIX matGoOrigin, matGoPrev;
            D3DXMatrixIdentity(&matGoOrigin);
            D3DXMatrixIdentity(&matGoPrev);
            D3DXMatrixTranslation(&matGoOrigin, -m_tInfo.vPos.x, -m_tInfo.vPos.y, -m_tInfo.vPos.z);
            D3DXMatrixTranslation(&matGoPrev, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

            for (auto& vertex : m_vVertexes)
            {
                //회전
                D3DXVec3TransformCoord(&vertex, &vertex, &matGoOrigin);
                D3DXVec3TransformCoord(&vertex, &vertex, &matRotate);
                D3DXVec3TransformCoord(&vertex, &vertex, &matGoPrev);
            }
            D3DXVec3TransformCoord(&m_tInfo.vLook, &m_tInfo.vLook, &matRotate);
        }
    }
#pragma endregion

    // 카드 뒤집기
    if (m_bIsOpen && !m_bFlipComplete)
    {
        // 회전 행렬 구하기
        D3DXMATRIX matRotate;
        D3DXMatrixIdentity(&matRotate);
        m_fFlipAngle += 3.f;
        D3DXMatrixRotationY(&matRotate, D3DXToRadian(3.f));

        // 원점, 복귀 이동행렬 구하기
        D3DXMATRIX matGoOrigin, matGoPrev;
        D3DXMatrixIdentity(&matGoOrigin);
        D3DXMatrixIdentity(&matGoPrev);
        D3DXMatrixTranslation(&matGoOrigin, -m_tInfo.vPos.x, -m_tInfo.vPos.y, -m_tInfo.vPos.z);
        D3DXMatrixTranslation(&matGoPrev, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

        // 뒤집기 회전~
        for (auto& vertex : m_vVertexes)
        {
            D3DXVec3TransformCoord(&vertex, &vertex, &matGoOrigin);
            D3DXVec3TransformCoord(&vertex, &vertex, &matRotate);
            D3DXVec3TransformCoord(&vertex, &vertex, &matGoPrev);
        }

        if (m_fFlipAngle > 180)
        {
            m_bFlipComplete = true;
            GETSINGLE(CCardMgr)->Set_DeterminingCard(this);
            GETSINGLE(CCardMgr)->IsPair();
        }
    }
    return 0;
}

void CCard::Late_Update()
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
            m_bIsOpen = true;
            m_bFlipComplete = false;
            m_fFlipAngle = 0.f;
        }
    }
}

void CCard::Render(HDC hDC)
{
    LPCSTR CardType = "card";
    switch (m_eType)
    {
    case HEART_1:
        CardType = "HEART_1";
        break;
    case HEART_2:
        CardType = "HEART_2";
        break;
    case HEART_3:
        CardType = "HEART_3";
        break;
    case SPADE_1:
        CardType = "SPADE_1";
        break;
    case SPADE_2:
        CardType = "SPADE_2";
        break;
    case SPADE_3:
        CardType = "SPADE_3";
        break;
    case CLOVER_1:
        CardType = "CLOVER_1";
        break;
    case CLOVER_2:
        CardType = "CLOVER_2";
        break;
    case CLOVER_3:
        CardType = "CLOVER_3";
        break;
    defualt:
        CardType = "card";
        break;
    }
    if (!m_bIsOpen)
    {
        __super::Draw_Vertex_Color(hDC, 0 , 0, 0);
    }
    else
    {
        __super::Draw_Vertex_Color(hDC, 255, 0, 0);
        TextOutA(hDC, m_tRect.left, m_tRect.top, CardType, lstrlenA(CardType));
    }
}

void CCard::Release()
{
    _sCardCnt--;
}
