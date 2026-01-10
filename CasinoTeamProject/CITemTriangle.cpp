#include "pch.h"
#include "CITemTriangle.h"
#include "CKeyMgr.h"
CITemTriangle::CITemTriangle()
{
	m_eRender = GAMEOBJECT;
}

CITemTriangle::~CITemTriangle()
{
}

void CITemTriangle::Initialize()
{
	m_tInfo.vPos.z = 0;
	m_tInfo.vPos.y = 25.f;
	m_fScale = 25.f;
	m_vPoint[0] = { m_tInfo.vPos.x,		 - m_fScale , 0 };
	m_vPoint[1] = { m_tInfo.vPos.x + 30, + m_fScale , 0 };
	m_vPoint[2] = { m_tInfo.vPos.x - 30, + m_fScale , 0 };
	m_vPos = { m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z };
	m_tInfo.vDir = { 1.f, 1.f, 1.f };
	
	m_fSpeed = 6.f;

	for (int i = 0; i < 3; ++i)
		m_vOriginal[i] = m_vPoint[i];

	if (m_tInfo.vDir.y == 1.f)
		//m_bSwitch = true;
	m_fPos = 0;

}

int CITemTriangle::Update()
{
	D3DXMATRIX matScale, matTrans;

	//m_tInfo.vPos.y += m_fSpeed;
	//if (m_tInfo.vPos.y >= WINCY / 2 + 50)
	//	m_tInfo.vPos.y = WINCY / 2 + 50;
	//else if (m_tInfo.vPos.y >= WINCY / 2 - 50 + m_fPos && !m_bSwitch)
	//	m_tInfo.vPos.y = WINCY / 2 - 50 + m_fPos;
	//
	//
	//D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	//D3DXMatrixScaling(&matScale, m_tInfo.vDir.x, m_tInfo.vDir.y, m_tInfo.vDir.z);
	//
	//m_tInfo.matWorld = matScale * matTrans;
	//
	//for (int i = 0; i < 3; ++i)
	//{
	//
	//	m_vPoint[i] = m_vOriginal[i];
	//	m_vPoint[i] -= {m_vPos.x, m_vPos.y, m_vPos.z};
	//
	//	D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	//}
    return 0;
}

void CITemTriangle::Late_Update()
{
	//if (m_bSwitch && m_tInfo.vPos.y >= WINCY / 2 + 50)
	//{
	//	m_tInfo.vDir.y -= 0.05f;
	//	m_tInfo.vDir.x -= 0.05f;
	//}
	//else if (!m_bSwitch && m_tInfo.vPos.y >= WINCY / 2 - 50)
	//{
	//	m_tInfo.vDir.y += 0.05f;
	//	m_fPos += m_fSpeed;
	//	if (fabsf(m_tInfo.vDir.y) >= 1.f)
	//	{
	//		m_fPos = 0.f;
	//		m_bSwitch = true;
	//		m_tInfo.vDir.y = 1.f;
	//		m_tInfo.vPos.y += m_fScale * 2;
	//	}
	//}
	//
	//if (m_bSwitch && m_tInfo.vDir.y < 0.f)
	//{
	//	m_bSwitch = false;
	//	m_tInfo.vDir.y = 0.f;
	//	m_tInfo.vDir.x = 1.f;
	//	m_tInfo.vPos.y = WINCY / 2 - 50.f;
	//}
}

void CITemTriangle::Render(HDC hDC)
{
	MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y , nullptr);
	for (int i = 1; i < 3; ++i)
	{
		LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y );
	}
	LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y );
}

void CITemTriangle::Release()
{
}
