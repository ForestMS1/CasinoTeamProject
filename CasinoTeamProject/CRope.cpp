#include "pch.h"
#include "CRope.h"
#include "CKeyMgr.h"
#include "CPlayerR.h"
#include "CObjMgr.h"
CRope::CRope()
{
    m_eRender = GAMEOBJECT;
	m_fAngle = 0.f;
}

CRope::~CRope()
{
}

void CRope::Initialize()
{
	m_RopePoint[0] = { WINCX / 16 + 25, WINCY / 2, 0 };
	for (int i = 1; i < 8; ++i)
	{
		m_RopePoint[i] = { (WINCX / 16 + 25) + float(i * 83) ,WINCY / 2, 0 };
	}
	m_RopePoint[8]  = { (WINCX - WINCX / 16) - 25,  WINCY / 2, 0 };

	m_tInfo.vPos = { WINCX / 2, WINCY / 2 , 0.f };
	m_fSpeed = 3.f;
	for (int i = 0; i < 9; ++i)
		m_RopeOriginal[i] = m_RopePoint[i];

	m_MaxY = WINCY / 2 - 200.f;
	m_MinY = WINCY / 2 + 200.f;
	m_bCheck = true;
	m_vPos = { WINCX / 2, WINCY - WINCY /2 -50  , 0 };

	m_vScale = { 1.f,1.f, 0.f};
}

int CRope::Update()
{
	D3DXMATRIX matScale, matRotX, matTrans;
	//m_tInfo.vLook =   m_vPos - m_tInfo.vPos;
	m_fAngle += m_fSpeed;

	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationX(&matRotX, D3DXToRadian(m_fAngle));
	
	m_tInfo.matWorld = matScale * matRotX * matTrans;

	for (int i = 1; i < 8; ++i)
	{
		m_RopePoint[i] = m_RopeOriginal[i];
		m_RopePoint[i] -= {m_vPos.x, m_vPos.y, 0};
		D3DXVec3TransformCoord(&m_RopePoint[i],&m_RopePoint[i],&m_tInfo.matWorld);
	}

    return 0;
}

void CRope::Late_Update()
{
	
}
void CRope::Render(HDC hDC)
{
	MoveToEx(hDC, m_RopePoint[0].x, m_RopePoint[0].y, nullptr);

	for (int i = 1; i < 9; ++i)
		LineTo(hDC, m_RopePoint[i].x, m_RopePoint[i].y);

	SetBkMode(hDC, 1); //ÆùÆ® ¹è°æ Á¦°Å
	SetTextColor(hDC, RGB(0, 0, 0)); //ÆùÆ® »ö»ó Èò»ö
	HFONT hFont, oldFont;
	hFont = CreateFont(40, 0, 0, 0, 400, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH || FF_ROMAN, L"¸¼Àº °íµñ");

	oldFont = (HFONT)SelectObject(hDC, hFont);
	swprintf_s(m_sZScore, L"SCORE : %d", dynamic_cast<CPlayerR*>(GETSINGLE(CObjMgr)->GetObjLayer(OBJ_PLAYER).front())->Get_Score());
	TextOut(hDC, 300, 5, m_sZScore, wcslen(m_sZScore));
	DeleteObject(oldFont);
}

void CRope::Release()
{
}
