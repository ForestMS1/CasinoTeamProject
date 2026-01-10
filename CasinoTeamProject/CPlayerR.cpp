#include "pch.h"
#include "CPlayerR.h"
#include "CKeyMgr.h"
#include "CObjMgr.h"
CPlayerR::CPlayerR()
{
    m_eRender = PLAYER;
	m_fMaxJump = 100.f;
	m_fMaxCheck;
	m_bJump = false;
	m_bFalling = false;
	m_bLineCheck = false;
	m_fBack = false;
	m_fY = 0.f;
	m_fHitY = 0.f;
	m_fHitTime = 0.f;
	m_bHit = false;
	m_iScore = 0;
}

CPlayerR::~CPlayerR()
{
}

void CPlayerR::Initialize()
{
	m_fScale = 25.f;
	m_vPoint[0] = { -m_fScale, -m_fScale, 0 };
	m_vPoint[1] = {  m_fScale, -m_fScale, 0 };
	m_vPoint[2] = {  m_fScale,  m_fScale, 0 };
	m_vPoint[3] = { -m_fScale,  m_fScale, 0 };

	m_tInfo.vPos = { WINCX/2 , WINCY - 100 , 0.f };
	m_tInfo.vDir = { 0.f,1.f,0.f };
	m_tInfo.vLook = { 0.f,1.f,1.f };

	m_vPos = { WINCX / 2, WINCY / 2,0.f };
	m_fSpeed = 3.f;
	for (int i = 0; i < 4; ++i)
		m_vOriginal[i] = m_vPoint[i];
	
	m_vScale = { 1.f,1.f,1.f };
	
	m_fT = 0.1f;
}

int CPlayerR::Update()
{
	D3DXMATRIX matScale, matTrans;

	//거리 비례해서 크기 조정 흠
	// float fDistance(0.f), fWidth(0.f), fHeight(0.f), fLength(0.f), m_fCheckScale(0.f);
	//if (!m_bJump)
	//{
	//	fWidth = (m_vPos.x - m_tInfo.vPos.x) * (m_vPos.x - m_tInfo.vPos.x);
	//	fHeight = (m_vPos.y - m_tInfo.vPos.y) * (m_vPos.y - m_tInfo.vPos.y);
	//	fLength = D3DXVec3Length(&m_tInfo.vPos);
	//	fDistance = sqrtf(fWidth + fHeight);
	//	m_fCheckScale = 1.f - fLength / fDistance;
	//	if (m_fCheckScale <= -1.3f)
	//		m_fCheckScale = -1.3f;
	//}
	if (!m_bHit)
	{
		Key_Input();
		Jump_Check();
		Falling_Check();
	}
	else
		Hitttttttt();
	
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	D3DXMatrixScaling(&matScale, m_vScale.x , m_vScale.y , m_vScale.z );

	m_tInfo.matWorld = matScale * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vOriginal[i], &m_tInfo.matWorld);
	}
	
    return 0;
}

void CPlayerR::Late_Update()
{
	if (!m_bHit)
	{

		if (m_bFalling && m_vCurrentPos.y < m_tInfo.vPos.y)
		{
			m_tInfo.vPos.y = m_vCurrentPos.y;
			m_bFalling = false;
		}

		if (m_tInfo.vPos.y <= WINCY / 2)
			m_bLineCheck = true;

	}
	if (m_bScore && !m_bFalling && !m_bJump)
	{
		++m_iScore;
		m_bScore = false;
	}
	if (Line_Check() && !m_bFalling && !m_bJump)
		m_tInfo.vPos.y = m_fY;

	if(m_fHitTime >= 10)
	{
		m_fHitTime = 0.f;
		m_bHit = false;
		--m_iScore;

		if (m_iScore < 0)
			m_iScore = 0;
	}

}

void CPlayerR::Render(HDC hDC)
{
	MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);
	
	for (int i = 1; i < 4; ++i)
		LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y);

	LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);
}

void CPlayerR::Release()
{
}

void CPlayerR::Key_Input()
{
	if (!m_bJump && !m_bFalling )
	{
		if (!m_bLineCheck)
		{
			if (GETSINGLE(CKeyMgr)->Get_KeyState('W'))
			{
				m_tInfo.vPos.y -= m_fSpeed;
			}
			if (GETSINGLE(CKeyMgr)->Get_KeyState('S'))
			{
				m_tInfo.vPos.y += m_fSpeed;
			}
		}

		if (GETSINGLE(CKeyMgr)->Get_KeyState('D'))
		{
			m_tInfo.vPos.x += m_fSpeed;
		}
		if (GETSINGLE(CKeyMgr)->Get_KeyState('A'))
		{
			m_tInfo.vPos.x -= m_fSpeed;
		}
	}
	if (!m_bJump && !m_bFalling && GETSINGLE(CKeyMgr)->Get_KeyState(VK_SPACE))
	{
		m_vCurrentPos = m_tInfo.vPos;
		m_fMaxCheck = m_tInfo.vPos.y - m_fMaxJump;
		m_bJump = true;

		m_fT = 0.f;
	}
}

void CPlayerR::Jump_Check()
{
	if (m_bJump)
	{
		if (m_tInfo.vPos.y >= m_fMaxCheck)
		{
			D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
			m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
		}
		else
		{
			m_bJump = false;
			m_bFalling = true;
			m_fMaxCheck = 0.f;
			
		}
	}
	
}

void CPlayerR::Falling_Check()
{
	if (m_bFalling)
	{
		m_fT += 0.1f;
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos += m_tInfo.vDir * 9.8 * m_fT;
	}
}

void CPlayerR::Hitttttttt()
{
	DWORD m_dwTime = GetTickCount(); 
	m_bFalling = false;
	m_bJump = false;
	m_bLineCheck = false;
	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

	if (m_dwTime - m_dwHitTIme > 60)
	{
		++m_fHitTime;
		m_dwHitTIme = m_dwTime;
	}
}

bool CPlayerR::Line_Check()
{
	if (m_bLineCheck)
	{
		float	x1 = 0;
		float	y1 = WINCY / 2 + 25;
		float	x2 = WINCX;
		float	y2 = WINCY / 2 + 25;
		
		m_fY = ((y2 - y1) / (x2 - x1)) * (m_tInfo.vPos.x - x1) + y1;
		 
		return 1;
	}

	return 0;
}
