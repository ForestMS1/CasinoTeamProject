#include "pch.h"
#include "CPosinShoot.h"
#include "CObjMgr.h"
#include "CPlayerL.h"
CPosinShoot::CPosinShoot()
{
	m_eRender = GAMEOBJECT;
}

CPosinShoot::~CPosinShoot()
{
}

void CPosinShoot::Initialize()
{
	m_fScale = 25.f;

	m_vPoint[0] = { -m_fScale ,-m_fScale, 0.f };
	m_vPoint[1] = {  m_fScale ,-m_fScale, 0.f };
	m_vPoint[2] = {  m_fScale , m_fScale, 0.f };
	m_vPoint[3] = { -m_fScale , m_fScale, 0.f };

	for (int i = 0; i < 4; ++i)
	{
		m_vPOne[i] = m_vPoint[i];
		m_vPTwo[i] = m_vPoint[i];
		m_vOriginal[i] = m_vPoint[i];
	}
	m_tInfo.vPos = { 400.f,200.f,0.f };
	
	for (int i = 0; i < 60; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m_vecPoint[i].push_back(m_vPoint[j]);

			m_vecOrignal[i].push_back(m_vPoint[j]);
		}
		
	}
	m_fAngle = 0.f;
	m_fSpeed = 0.15f;
	D3DXMATRIX matRotY, matRotZ, matRotX;
	for (int i = 0; i < 60; ++i)
	{
		m_vecMat.push_back(matRotY);

	}
	for (int i = 0; i < 60; ++i)
	{
		D3DXMatrixRotationZ(&m_vecMat[i], D3DXToRadian(i * 6 + m_fAngle));
	}

	for (int i = 0; i < 60; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			D3DXVec3TransformCoord(&m_vecPoint[i][j], &m_vecPoint[i][j], &m_vecMat[i]);
			D3DXVec3TransformCoord(&m_vecOrignal[i][j], &m_vecOrignal[i][j], &m_vecMat[i]);

		}
	}

}

int CPosinShoot::Update()
{

	D3DXMATRIX matRotX, matRotY, matRotZ, matTrans;
	D3DXMATRIX matWordone, matWordTwo;

	m_fAngle += m_fSpeed;
	//¤»¤»
	//D3DXMatrixRotationY(&matRotY,D3DXToRadian(m_fAngle));
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));

	
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.y);

	m_tInfo.matWorld = matTrans;
	matWordone = matRotY * matTrans;
	matWordTwo = matRotZ * matTrans;
	for (int i = 0; i < 60; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_vecPoint[i][j] = m_vecOrignal[i][j];
			D3DXVec3TransformCoord(&m_vecPoint[i][j], &m_vecOrignal[i][j], &m_tInfo.matWorld);
		}
		
	}
	//for (int i = 0; i < 4; ++i)
	//{
	//	D3DXVec3TransformCoord(&m_vPoint[i], &m_vOriginal[i], &m_tInfo.matWorld);
	//	D3DXVec3TransformCoord(&m_vPOne[i],  &m_vOriginal[i], &matWordone);
	//	D3DXVec3TransformCoord(&m_vPTwo[i],  &m_vOriginal[i], &matWordTwo);
	//}
	return 0;
}

void CPosinShoot::Late_Update()
{
	INFO tInfo;
	int irandX = (WINCX -100) - rand() % 700;
	int irandY = (100) + rand() % 150;

	tInfo = GETSINGLE(CObjMgr)->GetObjLayer(OBJ_PLAYER).front()->Get_Info();

	if (m_tInfo.vPos.x - m_fScale < tInfo.vPos.x && m_tInfo.vPos.x + m_fScale > tInfo.vPos.x &&
		m_tInfo.vPos.y - m_fScale < tInfo.vPos.y && m_tInfo.vPos.y + m_fScale > tInfo.vPos.y)
	{
		m_tInfo.vPos.x = irandX;
		m_tInfo.vPos.y = irandY;
	}
}

void CPosinShoot::Render(HDC hDC)
{
	//MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);
	//for (int i = 1; i < 4; ++i)
	//{
	//	LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y);
	//}
	//LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);
	//
	//MoveToEx(hDC, m_vPOne[0].x, m_vPOne[0].y, nullptr);
	//for (int i = 1; i < 4; ++i)
	//{
	//	LineTo(hDC, m_vPOne[i].x, m_vPOne[i].y);
	//}
	//LineTo(hDC, m_vPOne[0].x, m_vPOne[0].y);
	//
	//
	//MoveToEx(hDC, m_vPTwo[0].x, m_vPTwo[0].y, nullptr);
	//for (int i = 1; i < 4; ++i)
	//{
	//	LineTo(hDC, m_vPTwo[i].x, m_vPTwo[i].y);
	//}
	//LineTo(hDC, m_vPTwo[0].x, m_vPTwo[0].y);

	for (int i = 0; i < 60; ++i)
	{
		MoveToEx(hDC, m_vecPoint[i][0].x, m_vecPoint[i][0].y, nullptr);
		for (int j = 1; j < 4; ++j)
		{
			LineTo(hDC, m_vecPoint[i][j].x, m_vecPoint[i][j].y);
		}
		LineTo(hDC, m_vecPoint[i][0].x, m_vecPoint[i][0].y);

	}
}

void CPosinShoot::Release()
{
}
