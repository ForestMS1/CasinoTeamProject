#include "pch.h"
#include "CLineShoot.h"
#include "CKeyMgr.h"
CLineShoot::CLineShoot()
{
    m_eRender = GAMEOBJECT;
    m_bClick = false;
    m_bPull = false;

}

CLineShoot::~CLineShoot()
{
}

void CLineShoot::Initialize()
{
    m_vPoint[0] = {0.f, WINCY - 200, 0.f};
    m_vPoint[1] = {0.f, 0.f, 0.f};
    m_vPoint[2] = {WINCX, WINCY - 200, 0.f};

    m_vOriginal[1] = m_vPoint[1];
    m_vOriginal[0] = { 0.f, WINCY - 200, 0.f };

    m_tInfo.vPos = { WINCX/2, WINCY - 200, 0.f };

    m_vCurLinePos = m_tInfo.vPos;
    m_fSpeed = 20.f;
}

int CLineShoot::Update()
{

    D3DXMATRIX matRotX, matTrans;
    Key_Input();
    
    if (m_tInfo.vPos.y <= WINCY - 200)
    {
        m_tInfo.vPos.y = m_vCurLinePos.y;
    }
    
    if (!m_bClick && m_bPull)
    {
        m_tInfo.vLook = m_vCurLinePos - m_tInfo.vPos;
        D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);
        D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
        m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

    }

    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
    

    m_tInfo.matWorld =  matTrans;
    
    D3DXVec3TransformCoord(&m_vPoint[1], &m_vOriginal[1],&m_tInfo.matWorld );
    

    return 0;
}

void CLineShoot::Late_Update()
{
    if (m_tInfo.vPos.y <= WINCY - 200)
    {
        m_bPull = false;
    }
}

void CLineShoot::Render(HDC hDC)
{

    MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);

    LineTo(hDC, m_vPoint[1].x, m_vPoint[1].y);
    LineTo(hDC, m_vPoint[2].x, m_vPoint[2].y);

}

void CLineShoot::Release()
{
}

void CLineShoot::Key_Input()
{

    if (GETSINGLE(CKeyMgr)->Key_Pressing(VK_LBUTTON))
    {

        POINT pt;
        D3DXVECTOR3 vptMouse;
        GetCursorPos(&pt);
        ScreenToClient(g_hWnd, &pt);
        vptMouse = { FLOAT(pt.x), FLOAT(pt.y),0.f };
        m_bClick = true;
        m_tInfo.vPos = vptMouse;
        m_bPull = true;
    }
    else
    {
        m_bClick = false;
    }
}