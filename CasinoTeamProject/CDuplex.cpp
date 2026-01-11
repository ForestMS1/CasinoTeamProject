#include "pch.h"
#include "CDuplex.h"

CDuplex::CDuplex()
{
}

CDuplex::~CDuplex()
{
}

void CDuplex::Initialize()
{
    m_fAngle = 0.f;
    m_tInfo.vPos = { 400,450,0 };
    m_tInfo.vDir = { 1.f,0.f,0.f };
}

int CDuplex::Update()
{
    D3DXMATRIX matScale, matRotX, matTrans;

    D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
    D3DXMatrixRotationX(&matRotX, m_fAngle);
    D3DXMatrixTranslation(&matTrans,
        m_tInfo.vPos.x,
        m_tInfo.vPos.y,
        m_tInfo.vPos.z);

    m_tInfo.matWorld = matScale * matRotX * matTrans;

    return 0;
}

void CDuplex::Late_Update()
{
}

void CDuplex::Render(HDC hDC)
{
    float fHalfWidth = 50.f;
    float fHalfHeight = 8.f;

    D3DXVECTOR3 vLocal[4] = {
        D3DXVECTOR3(-fHalfWidth, -fHalfHeight, 0.f),
        D3DXVECTOR3(fHalfWidth, -fHalfHeight, 0.f),
        D3DXVECTOR3(fHalfWidth,  fHalfHeight, 0.f),
        D3DXVECTOR3(-fHalfWidth,  fHalfHeight, 0.f)
    };
    for (int i = 0; i < 4; ++i) {
        D3DXVec3TransformCoord(&vWorld, &vLocal[i], &m_tInfo.matWorld);
        tPoints[i].x = (LONG)(vWorld.x);
        tPoints[i].y = (LONG)(vWorld.y);
    }
}

void CDuplex::Release()
{
}