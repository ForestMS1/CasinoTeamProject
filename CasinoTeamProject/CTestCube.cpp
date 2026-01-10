#include "pch.h"
#include "CTestCube.h"
#include "CKeyMgr.h"

// webhook 테스트 주석

// 프레임워크 테스트용 객체입니다.

CTestCube::CTestCube()
{
    // 렌더 순서를 지정해주셔야 에러가 발생하지 않습니다!
    m_eRender = PLAYER;
}

CTestCube::~CTestCube()
{
}

void CTestCube::Initialize()
{
    m_tInfo.vPos = { 400, 300, 0 };
    m_tInfo.vDir = { 1.f, 0.f, 0.f };
}

int CTestCube::Update()
{
    if (GETSINGLE(CKeyMgr)->Key_Pressing(VK_UP))
    {
        m_tInfo.vPos.y -= 10.f;
    }
    if (GETSINGLE(CKeyMgr)->Key_Pressing(VK_DOWN))
    {
        m_tInfo.vPos.y += 10.f;
    }
    if (GETSINGLE(CKeyMgr)->Key_Pressing(VK_LEFT))
    {
        m_tInfo.vPos.x -= 10.f;
    }
    if (GETSINGLE(CKeyMgr)->Key_Pressing(VK_RIGHT))
    {
        m_tInfo.vPos.x += 10.f;
    }
    return 0;
}

void CTestCube::Late_Update()
{
}

void CTestCube::Render(HDC hDC)
{
    Ellipse(hDC,
        int(m_tInfo.vPos.x - 50.f),
        int(m_tInfo.vPos.y - 50.f),
        int(m_tInfo.vPos.x + 50.f),
        int(m_tInfo.vPos.y + 50.f));
}

void CTestCube::Release()
{
}
