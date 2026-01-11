#include "pch.h"
#include "CPlayerL.h"
#include "CObjMgr.h"
#include "CLineShoot.h"
#include "CKeyMgr.h"
CPlayerL::CPlayerL()
{
    m_eRender = PLAYER;
    m_bShot = false;
    m_bFalling = true;
    m_bJump = false;
    m_bPullingCheck = false;
    m_fMaxCharge = 300.f;
    m_fMinCharge = 0.f;
    m_bCharging = true;
    m_bLookCheck = true;
    m_iAngleCount = 0;

    m_bSpinCheck = true;
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
    m_vPosin[0] = {0.f,0.f,0.f};
    m_vPosin[1] = {200.f,0.f,0.f};
    m_fang = 45.f;
    m_tPosin.vPos = { 0.f,0.f,0.f };
    for (int i = 0; i < 4; ++i)
        m_vOriginal[i] = m_vPoint[i];

    for (int i = 0; i < 2; ++i)
        m_vPosinOriginal[i] = m_vPosin[i];
    
    

    m_fPosinSpeed = -3.f;
    m_fAngle = 0.f;
    m_fSpeed = 3.f;
    m_fPower = 1.f;
    m_tInfo.vDir = { 0.f, 0.f, 0.f };
    m_ft = 0.f;
    m_tInfo.vLook = { 0.f, 0.f, 0.f };
    m_fPosinAngle = -90.f;
}


int CPlayerL::Update()
{
    D3DXMATRIX matScale, matRotZ, matTrans;
    D3DXMATRIX matPosinRotZ, matPosinTrans;
    D3DXVECTOR3 vptMouse, vZeroChek;
    D3DXVECTOR3 vLeftLook, vRightLook, vPosinNormal;
    D3DXVECTOR3 vCross, vNormal1, vNormal2;
    POINT pt; 
    float angle(0.f);
    float fLeftAngle(0.f);
    float fRightAngle(0.f);

    Set_Target(GETSINGLE(CObjMgr)->GetObjLayer(OBJ_LINE).front());

    GetCursorPos(&pt);
    ScreenToClient(g_hWnd, &pt);
    vptMouse = { FLOAT(pt.x), FLOAT(pt.y),0.f };
    vZeroChek = { 0.f,0.f,0.f };
    
    if (GETSINGLE(CKeyMgr)->Key_Pressing(VK_LBUTTON) && m_tInfo.vPos.y >= WINCY - 200)
    {
        m_bPullingCheck = true;
        m_bCharging = true;

        vLeftLook = { 0.f,   WINCY - 200,0.f };
       
        vLeftLook  =  vLeftLook  - vptMouse;
        vRightLook =  m_vPosin[1] - vptMouse;
           
        D3DXVec3Normalize(&vLeftLook, &vLeftLook);
        D3DXVec3Normalize(&vRightLook, &vRightLook);

        fLeftAngle = D3DXVec3Dot(&vLeftLook, &vRightLook);
        fLeftAngle = acosf(fLeftAngle);
        fLeftAngle = D3DXToDegree(fLeftAngle);


        vRightLook = { WINCX ,WINCY - 200,0.f };
        vLeftLook  = vRightLook  - vptMouse;
        vRightLook = m_vPosin[1] - vptMouse;

        D3DXVec3Normalize(&vLeftLook, &vLeftLook);
        D3DXVec3Normalize(&vRightLook, &vRightLook);

        fRightAngle = D3DXVec3Dot(&vLeftLook, &vRightLook);
        fRightAngle = acosf(fRightAngle);
        fRightAngle = D3DXToDegree(fRightAngle);
        
        if (fLeftAngle < 15 && m_fPosinSpeed <0)
            fLeftAngle = 9;

        if (fRightAngle < 15 && m_fPosinSpeed >0)
            fRightAngle = 9;

        if ((int)fLeftAngle < 10 )
        {
            m_fPosinSpeed *= -1.f;
        }
        else if ((int)fRightAngle < 10 )
        {
            m_fPosinSpeed *= -1.f;

        }
        // if ((int)fLeftAngle >= 0 && (int)fLeftAngle < 3)
       //     m_fPosinSpeed *= -1.f;
       // else if((int)fRightAngle >= 0 && (int)fRightAngle < 3)
       //     m_fPosinSpeed *= -1.f;

        m_fPosinAngle += m_fPosinSpeed;

        m_tPosin.vLook = m_vPosin[1] - vptMouse;
    }
    else
    {
        m_fPosinAngle = -90;
        m_bCharging = false;
    }
    if (dynamic_cast<CLineShoot*>(GETSINGLE(CObjMgr)->GetObjLayer(OBJ_LINE).front())->Get_Click())
    {
        if (m_bPullingCheck)
        {
            //당겨진 라인 추적
            m_tInfo.vLook = vLineCheck - m_tInfo.vPos;
            D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);
            D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
            
            m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

            m_iAngleCount = 0;
            //두 점이랑 현재 라인 당겨진 위치랑 내적 비교
            for (int i = 0; i < 2; ++i)
            {
                D3DXVec3Normalize(&vNormal1, &m_vCheckAngle[i]);
                D3DXVec3Normalize(&vNormal2, &vLineCheck);
                angle = acosf(D3DXVec3Dot(&vNormal1, &vNormal2));
                
                angle = D3DXToDegree(angle);

                if (angle > 3 )
                {
                    ++m_iAngleCount;
                    if (m_iAngleCount == 2)
                        continue;
                    if (m_tInfo.vLook.x < 0)
                        m_fAngle -= 3.1f;
                    else
                        m_fAngle += 3.1f;
                }
            }
            
        }
    }
    if (m_bJump && !m_bCharging)
    {
        //점프
        if (WINCY / 2 - m_fMaxCharge >= m_tInfo.vPos.y)
        {
            m_bJump = false;
            m_bFalling = true;
        }
        else
        {
            D3DXVec3Normalize(&m_tPosin.vLook, &m_tPosin.vLook);
           
            m_tInfo.vPos += m_tPosin.vLook * m_fSpeed * m_fPower;
            m_fAngle += m_fPower;
        }
    }
    //낙하
    if (m_bFalling && !m_bJump && !m_bCharging)
    {
        m_ft += 0.1f;
        m_tInfo.vPos.y += m_fSpeed * m_ft;
        m_fAngle       += m_fSpeed * m_ft;
    }
    else m_ft = 0.f;
    if (!m_bFalling && !m_bJump && !m_bCharging)
    {
        //각도 원상태로 보정
        m_fang = m_fAngle / 45.f;
        m_fAngle -= m_fAngle;
        if(m_fAngle / 45.f != 0)
            m_fAngle += 3.f;

#ifdef _DEBUG
        cout << "x" << m_fang << endl;
#endif          
    }

    D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
    D3DXMatrixTranslation(&matTrans,m_tInfo.vPos.x,m_tInfo.vPos.y,m_tInfo.vPos.z);
    


    m_tInfo.matWorld = matTrans;
    
    for (int i = 0; i < 4; ++i)
    {
        m_vPoint[i] = m_vOriginal[i];
        D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &matRotZ); //로컬좌표 회전
        D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld); // 로컬좌표 회전된거에 웓드좌표 합치기
        m_vCheckAngle[i] = m_vPoint[i] - m_vOriginal[i]; // 점에 대하여 각도 비교를 위함
        m_vSpin = m_vPoint[0];
    }


    //포신
    D3DXMatrixRotationZ(&matPosinRotZ, D3DXToRadian(m_fPosinAngle));
  
    m_tPosin.vPos = vptMouse;
    m_vPosin[0]   = vptMouse;

    D3DXMatrixTranslation(&matPosinTrans, m_tPosin.vPos.x, m_tPosin.vPos.y, m_tPosin.vPos.z);

    m_tPosin.matWorld = matPosinRotZ * matPosinTrans;
    

    m_vPosin[1] = m_vPosinOriginal[1];
    D3DXVec3TransformCoord(&m_vPosin[1], &m_vPosin[1], &m_tPosin.matWorld);
    return 0;
}

void CPlayerL::Late_Update()
{

    if(m_tInfo.vPos.x <=0 || m_tInfo.vPos.x >= WINCX)
    {
        m_tInfo.vPos = { 400.f, 300.f,0.f };
        m_bJump = false;
        m_bFalling = true;
    }

    float x1, y1, x2, y2;
    m_tLine = m_pTarget->Get_Info();
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
            m_bSpinCheck = true;
            m_bFalling = false;
        }
        else
            m_bFalling = true;
    }
   
    DWORD dwTime = GetTickCount();

    if (m_bCharging)
    {
       m_fMinCharge += m_fSpeed;
       m_fMaxCharge = m_fMinCharge;

       if (dwTime - m_dwChargeTime > 300)
       {
           m_fPower += 0.5f;
           m_dwChargeTime = dwTime;
       }
    }

    if (m_fPower >= 10)
        m_fPower = 10;

    if (m_fMinCharge >= 350)
    {
        m_fMinCharge = 350.f;
        m_fMaxCharge = 350.f;
    }
    if (!m_bCharging && m_bPullingCheck)
    {
        m_bJump = true;
        m_fMinCharge = 0.f;
        m_bPullingCheck = false;
    }
}

void CPlayerL::Render(HDC hDC)
{
    MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);

    for (int i = 1; i < 4; ++i)
        LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y);

    LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);

    if (m_bCharging)
    {
        MoveToEx(hDC, m_vPosin[0].x, m_vPosin[0].y, nullptr);
        LineTo(hDC, m_vPosin[1].x, m_vPosin[1].y);
    }
}

void CPlayerL::Release()
{
}
