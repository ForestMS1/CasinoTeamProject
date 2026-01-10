#include "pch.h"
#include "CITemSquare.h"

CITemSquare::CITemSquare()
{
	m_eRender = GAMEOBJECT;
}

CITemSquare::~CITemSquare()
{
}

void CITemSquare::Initialize()
{
	m_tInfo.vPos.y = 25;
	m_tInfo.vPos.z = 0;
	m_fScale = 25.f;
	m_vPoint[0] = { m_tInfo.vPos.x - m_fScale, -m_fScale, 0 };
	m_vPoint[1] = { m_tInfo.vPos.x + m_fScale, -m_fScale, 0 };
	m_vPoint[2] = { m_tInfo.vPos.x + m_fScale,  m_fScale, 0 };
	m_vPoint[3] = { m_tInfo.vPos.x - m_fScale,  m_fScale, 0 };

	m_vPos = { m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z };
	m_tInfo.vDir = { 1.f, 1.f, 1.f };

	m_fSpeed = 2.f;
	for (int i = 0; i < 4; ++i)
		m_vOriginal[i] = m_vPoint[i];
}

int CITemSquare::Update()
{
	//D3DXMATRIX  matScale, matTrans;
	//
	//m_tInfo.vPos.y += m_fSpeed;
	//if (m_tInfo.vPos.y >= WINCY / 2 + 50)
	//	m_tInfo.vPos.y = WINCY / 2 + 50;
	//else if (m_tInfo.vPos.y >= WINCY / 2 - 50 && !m_bSwitch)
	//	m_tInfo.vPos.y = WINCY / 2 - 50;
	//
	//D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	//D3DXMatrixScaling(&matScale, m_tInfo.vDir.x, m_tInfo.vDir.y, m_tInfo.vDir.z);
	//
	//m_tInfo.matWorld = matScale * matTrans;
	//
	//	for (int i = 0; i < 4; ++i)
	//	{
	//		m_vPoint[i] = m_vOriginal[i];
	//		m_vPoint[i] -= {m_vPos.x, m_vPos.y, m_vPos.z};
	//
	//		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	//	}
		return 0;
}

void CITemSquare::Late_Update()
{
	//if (m_bSwitch && m_tInfo.vPos.y >= WINCY / 2 + 50)
	//{
	//	m_tInfo.vDir.y -= 0.05f;
	//}
	//else if (!m_bSwitch && m_tInfo.vPos.y >= WINCY / 2 - 50)
	//{
	//	m_tInfo.vDir.y -= 0.05f;
	//	if (fabsf(m_tInfo.vDir.y) >= 1.f)
	//	{
	//		m_bSwitch = true;
	//		m_tInfo.vDir.y = 1.f;
	//		m_tInfo.vPos.y += m_fScale *2;
	//	}
	//}
	//
	//if (m_bSwitch && m_tInfo.vDir.y < 0.f)
	//{
	//	m_bSwitch = false;
	//	m_tInfo.vDir.y = 0.f;
	//	m_tInfo.vPos.y = WINCY / 2 - 50.f;
	//}
}

void CITemSquare::Render(HDC hDC)
{
	MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);

	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y);
	}
		
	LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y );
}

void CITemSquare::Release()
{
}
