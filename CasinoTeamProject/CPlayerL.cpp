#include "pch.h"
#include "CPlayerL.h"
#include "CObjMgr.h"
#include "CLineShoot.h"
CPlayerL::CPlayerL()
{
    m_eRender = PLAYER;
    m_bShot = false;
    m_bFalling = true;
    m_bJump = false;
    
    m_fMaxCharge = 300.f;
    m_fMinCharge = 0.f;
      
}

CPlayerL::~CPlayerL()
{
}

void CPlayerL::Initialize()
{
    m_fScale = 25.f;
    m_tInfo.vPos = { 400.f, 300.f,0.f };
    m_vPos = m_tInfo.vPos;
    m_vPoint[0] = { -m_fScale, -m_fScale ,0.f };
    m_vPoint[1] = {  m_fScale, -m_fScale ,0.f };
    m_vPoint[2] = {  m_fScale,  m_fScale ,0.f };
    m_vPoint[3] = { -m_fScale,  m_fScale ,0.f };

    for (int i = 0; i < 4; ++i)
        m_vOriginal[i] = m_vPoint[i];

    m_fAngle = 0.f;
    m_fSpeed = 3.f;
    
    m_tInfo.vDir = { 0.f, 0.f, 0.f };
    m_tInfo.vLook = { 0.f, 0.f, 0.f };
}


int CPlayerL::Update()
{
    D3DXMATRIX matScale, matRotZ, matTrans;
    D3DXVECTOR3 vptMouse;
    D3DXVECTOR3 vLineCheck, vLineOriginal, vCross, vNormal;
    POINT pt; 
    float angle;
    Set_Target(GETSINGLE(CObjMgr)->GetObjLayer(OBJ_LINE).front());
    m_tLine = m_pTarget->Get_Info();

    GetCursorPos(&pt);
    ScreenToClient(g_hWnd, &pt);
    vptMouse = { FLOAT(pt.x), FLOAT(pt.y),0.f };
    vLineOriginal = { 0.f, WINCY - 200, 0.f };
    D3DXVec3TransformCoord(&vLineCheck, &vLineOriginal, &m_tLine.matWorld);

    D3DXVec3Cross(&vCross, &vLineCheck, &vLineOriginal);
    D3DXVec3Normalize(&vCross, &vCross);
    D3DXVec3Normalize(&vNormal, &m_tInfo.vPos);

    angle = acosf(D3DXVec3Dot(&vNormal ,&vCross ));

    if (dynamic_cast<CLineShoot*>(GETSINGLE(CObjMgr)->GetObjLayer(OBJ_LINE).front())->Get_Click())
    {
        if (!m_bFalling && !m_bJump)
        {
            m_tInfo.vLook = vLineCheck - m_tInfo.vPos;
            D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);
           
            D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);

            m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
        }
        else
        {
            
        }
    }

    if (m_bFalling && !m_bJump)
    {
        m_tInfo.vPos.y += m_fSpeed;
    }
    //if (angle != 1)
    //    m_fAngle += m_fSpeed;

    #ifdef _DEBUG
        cout << "Dir X : " << (float)angle <<endl;
    #endif
    D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
    D3DXMatrixTranslation(&matTrans,m_tInfo.vPos.x,m_tInfo.vPos.y,m_tInfo.vPos.z);

    m_tInfo.matWorld =  matRotZ * matTrans;
    
    for (int i = 0; i < 4; ++i)
    {
        m_vPoint[i] = {0, 0, 0};
        D3DXVec3TransformCoord(&m_vPoint[i], &m_vOriginal[i], &m_tInfo.matWorld);
    }
    return 0;
}

void CPlayerL::Late_Update()
{
    //#ifdef _DEBUG
    //        cout << "Dir X : " << m_tInfo.vDir.x<< "\t" << "Dir Y :" << m_tInfo.vDir.y << endl;
    //        cout << "Pos X : " << m_tInfo.vPos.x << "\t" << "Pos Y :" << m_tInfo.vPos.y << endl;
    //#endif
    D3DXVECTOR3 vLineCheck, vLineOriginal;
    float x1, y1, x2, y2;
    vLineOriginal = { 0.f, 0.f, 0.f };

    D3DXVec3TransformCoord(&vLineCheck, &vLineOriginal, &m_tLine.matWorld);
    if (!m_bJump && !m_bFalling &&
        dynamic_cast<CLineShoot*>(GETSINGLE(CObjMgr)->GetObjLayer(OBJ_LINE).front())->Get_Click()||
        dynamic_cast<CLineShoot*>(GETSINGLE(CObjMgr)->GetObjLayer(OBJ_LINE).front())->Get_Pull())
    {
        if (m_tInfo.vPos.x >= 0 && vLineCheck.x >= m_tInfo.vPos.x)
        {
            x1 = 0;
            y1 = WINCY - 200;
            x2 = vLineCheck.x;
            y2 = vLineCheck.y;
        }
        else
        {
            x1 = vLineCheck.x;
            y1 = vLineCheck.y;
            x2 = WINCX;
            y2 = WINCY - 200;
        }
        float f1;
        f1 = ((y2 - y1) / (x2 - x1)) * (m_tInfo.vPos.x - x1) + y1 - m_fScale;
        if (f1 >= m_tInfo.vPos.y)
            m_tInfo.vPos.y += m_fSpeed;
        else
            m_tInfo.vPos.y = f1;
    }
    else
    {
        if (m_tInfo.vPos.y >= WINCY - 200 - m_fScale)
        {
            m_tInfo.vPos.y = WINCY - 200 - m_fScale;
            
            m_bFalling = false;
        }
        else
            m_bFalling = true;
    }
    DWORD dwTime = GetTickCount();


    if (dynamic_cast<CLineShoot*>(GETSINGLE(CObjMgr)->GetObjLayer(OBJ_LINE).front())->Get_Pull() &&
        !dynamic_cast<CLineShoot*>(GETSINGLE(CObjMgr)->GetObjLayer(OBJ_LINE).front())->Get_Click())
        m_bJump = true;

    if (m_bJump)
    {
        if (dwTime - m_dwChargeTime > 60)
        {
            m_fMinCharge += m_fSpeed;
            m_dwChargeTime = dwTime;
        }
    }
        if (m_fMinCharge >= m_fMaxCharge)
            m_bJump = false;
    
}

void CPlayerL::Render(HDC hDC)
{
    MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);

    for (int i = 1; i < 4; ++i)
        LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y);

    LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);
}

void CPlayerL::Release()
{
}
