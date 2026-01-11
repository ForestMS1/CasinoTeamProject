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
    //m_iIndex = _sCardCnt-1;
}

CCard::CCard(CARDTYPE _type)
    : m_bIsOpen(false),
    m_bFlipComplete(false),
    m_fFlipAngle(0.f)
{
    m_eRender = GAMEOBJECT;
    _sCardCnt++;
    //m_iIndex = _sCardCnt - 1;
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

#pragma region 문양별로 점찍기
    // 다이아
    float fSymW = fHalfX * 0.4f; // 문양 너비
    float fSymH = fHalfY * 0.4f; // 문양 높이
    // 스페이드
    float fBodyBottom = m_tInfo.vPos.y + fHalfY * 0.4f;
    // 별
    float fOuterRadius = m_tInfo.vScale.x * 0.5f;    // 바깥쪽 큰 반지름
    float fInnerRadius = fOuterRadius * 0.4f;      // 안쪽 작은 반지름 (0.4 ~ 0.5 추천)

    // 도넛
    float fDoughnutOuterRadius = m_tInfo.vScale.x * 0.5f; // 바깥쪽 반지름
    float fDoughnutInnerRadius = fDoughnutOuterRadius * 0.4f;     // 안쪽 구멍 반지름 (0.4 ~ 0.6 추천)
    int iSegment = 30; // 원을 얼마나 부드럽게 그릴지 결정 (점의 개수)

    // 십자가 팔의 두께
    float fThickX = fHalfX * 0.3f;
    float fThickY = fHalfY * 0.3f;

    // 팩맨
    float fRadius = m_tInfo.vScale.x * 0.5f;
    float fMouthAngle = 35.f; // 입이 벌어진 각도 (한쪽 기준 35도, 총 70도)

    switch (m_eType)
    {
    case HEART_1:
#pragma region 중앙 다이아몬드 문양
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y - fSymH, 0.f));          // 문양 상단
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x + fSymW, m_tInfo.vPos.y, 0.f));          // 문양 우측
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y + fSymH, 0.f));          // 문양 하단
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x - fSymW, m_tInfo.vPos.y, 0.f));          // 문양 좌측
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y - fSymH, 0.f));          // 루프 닫기
#pragma endregion
        break;
    case HEART_2:
#pragma region 매끄러운 하트 좌표 생성
        for (int i = 0; i <= 360; i += 10)
        {
            float fAngle = D3DXToRadian((float)i);

            // 하트 곡선 공식 (Parametric Heart Equation)
            // x = 16 sin^3(t)
            // y = 13 cos(t) - 5 cos(2t) - 2 cos(3t) - cos(4t)

            float x = 16.f * powf(sinf(fAngle), 3.f);
            float y = -(13.f * cosf(fAngle) - 5.f * cosf(2.f * fAngle) - 2.f * cosf(3.f * fAngle) - cosf(4.f * fAngle));

            float fSize = m_tInfo.vScale.x * 0.025f;

            m_dvEmblemVertex.push_back(D3DXVECTOR3(
                m_tInfo.vPos.x + x * fSize,
                m_tInfo.vPos.y + y * fSize,
                0.f));
        }
#pragma endregion
        break;
    case HEART_3:
#pragma region 세모
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y - fHalfY * 0.5f, 0.f));
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x + fHalfX * 0.5f, m_tInfo.vPos.y + fHalfY * 0.5f, 0.f));
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x - fHalfX * 0.5f, m_tInfo.vPos.y + fHalfY * 0.5f, 0.f));
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y - fHalfY * 0.5f, 0.f));
#pragma endregion
        break;
    case SPADE_1:
#pragma region 스페이드 좌표
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y - fHalfY, 0.f));
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x + fHalfX, m_tInfo.vPos.y + fHalfY * 0.1f, 0.f));
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x + fHalfX * 0.2f, fBodyBottom, 0.f));
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x + fHalfX * 0.4f, m_tInfo.vPos.y + fHalfY, 0.f));
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x - fHalfX * 0.4f, m_tInfo.vPos.y + fHalfY, 0.f));
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x - fHalfX * 0.2f, fBodyBottom, 0.f));
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x - fHalfX, m_tInfo.vPos.y + fHalfY * 0.1f, 0.f));
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y - fHalfY, 0.f));
#pragma endregion
        break;
    case SPADE_2:
#pragma region 별 좌표 생성
        for (int i = 0; i <= 10; ++i)
        {
            float fAngle = D3DXToRadian(i * 36.f - 90.f);
            float fCurrentRadius = (i % 2 == 0) ? fOuterRadius : fInnerRadius;

            m_dvEmblemVertex.push_back(D3DXVECTOR3(
                m_tInfo.vPos.x + cosf(fAngle) * fCurrentRadius,
                m_tInfo.vPos.y + sinf(fAngle) * fCurrentRadius,
                0.f));
        }
#pragma endregion
        break;
    case SPADE_3:
#pragma region 도넛(고리) 좌표 생성
        for (int i = 0; i <= iSegment; ++i)
        {
            float fAngle = D3DXToRadian(i * (360.f / iSegment));

            // 1. 바깥쪽 원의 점
            m_dvEmblemVertex.push_back(D3DXVECTOR3(
                m_tInfo.vPos.x + cosf(fAngle) * fDoughnutOuterRadius,
                m_tInfo.vPos.y + sinf(fAngle) * fDoughnutOuterRadius,
                0.f));

            // 2. 안쪽 원의 점 (지그재그로 연결하기 위해 바로 이어서 추가)
            m_dvEmblemVertex.push_back(D3DXVECTOR3(
                m_tInfo.vPos.x + cosf(fAngle) * fDoughnutInnerRadius,
                m_tInfo.vPos.y + sinf(fAngle) * fDoughnutInnerRadius,
                0.f));
        }
#pragma endregion
        break;
    case CLOVER_1:
#pragma region 십자가 좌표 (시계 방향)
        // 상단 기둥
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x - fThickX, m_tInfo.vPos.y - fHalfY, 0.f));
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x + fThickX, m_tInfo.vPos.y - fHalfY, 0.f));

        // 오른쪽 팔 상단
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x + fThickX, m_tInfo.vPos.y - fThickY, 0.f));
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x + fHalfX, m_tInfo.vPos.y - fThickY, 0.f));

        // 오른쪽 팔 하단
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x + fHalfX, m_tInfo.vPos.y + fThickY, 0.f));
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x + fThickX, m_tInfo.vPos.y + fThickY, 0.f));

        // 하단 기둥
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x + fThickX, m_tInfo.vPos.y + fHalfY, 0.f));
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x - fThickX, m_tInfo.vPos.y + fHalfY, 0.f));

        // 왼쪽 팔 하단
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x - fThickX, m_tInfo.vPos.y + fThickY, 0.f));
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x - fHalfX, m_tInfo.vPos.y + fThickY, 0.f));

        // 왼쪽 팔 상단
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x - fHalfX, m_tInfo.vPos.y - fThickY, 0.f));
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x - fThickX, m_tInfo.vPos.y - fThickY, 0.f));

        // 마지막 연결
        m_dvEmblemVertex.push_back(m_dvEmblemVertex[0]);
#pragma endregion
        break;
    case CLOVER_2:
#pragma region 팩맨 좌표 생성
        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f));

        for (float fAngle = fMouthAngle; fAngle <= 360.f - fMouthAngle; fAngle += 10.f)
        {
            float fRadian = D3DXToRadian(fAngle);
            m_dvEmblemVertex.push_back(D3DXVECTOR3(
                m_tInfo.vPos.x + cosf(fRadian) * fRadius,
                m_tInfo.vPos.y - sinf(fRadian) * fRadius, // y축 반전 (컴퓨터 좌표계)
                0.f));
        }

        m_dvEmblemVertex.push_back(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f));
#pragma endregion
        break;
    case CLOVER_3:
#pragma region 오각형 좌표 생성
        // 360도를 5등분하여 72도씩 회전하며 점을 찍음
        for (int i = 0; i <= 5; ++i)
        {
            // -90도를 더해 12시 방향(상단)부터 시작하도록 설정
            float fAngle = D3DXToRadian(i * 72.f - 90.f);

            m_dvEmblemVertex.push_back(D3DXVECTOR3(
                m_tInfo.vPos.x + cosf(fAngle) * fRadius,
                m_tInfo.vPos.y + sinf(fAngle) * fRadius,
                0.f));
        }
#pragma endregion
        break;
    defualt:
        break;
    }
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
        for (auto& vertex : m_dvEmblemVertex)
        {
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
        for (auto& vertex : m_dvEmblemVertex)
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

    if (GETSINGLE(CKeyMgr)->Key_Pressing(VK_LBUTTON) && !m_bIsOpen)
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

        if (!m_dvEmblemVertex.empty() && m_fFlipAngle > 90.f)
        {
            MoveToEx(hDC, m_dvEmblemVertex[0].x, m_dvEmblemVertex[0].y, nullptr);
            for (auto& emblem : m_dvEmblemVertex)
            {
                LineTo(hDC, emblem.x, emblem.y);
            }
            LineTo(hDC, m_dvEmblemVertex[0].x, m_dvEmblemVertex[0].y);
        }

        //TextOutA(hDC, m_tRect.left, m_tRect.top, CardType, lstrlenA(CardType));
    }
}

void CCard::Release()
{
    _sCardCnt--;
}
