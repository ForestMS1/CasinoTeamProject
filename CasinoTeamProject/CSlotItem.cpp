#include "pch.h"
#include "CSlotItem.h"
#include "CITemSquare.h"
#include "CITemDiamond.h"
#include "CITemSeven.h"
#include "CITemTriangle.h"
#include "CObjMgr.h"
#include "CObj.h"
#include "CAbstractFactory.h"
CSlotItem::CSlotItem()
{
	m_eRender = GAMEOBJECT;
}

CSlotItem::~CSlotItem()
{
	Release();
}

void CSlotItem::Initialize()
{

	m_tInfo.vPos.y = 50;
	m_tInfo.vPos.z = 0;
	m_vPoint[0]	   = { m_tInfo.vPos.x - 50, WINCY / 2 - 50, 0 };
	m_vPoint[1]	   = { m_tInfo.vPos.x + 50, WINCY / 2 - 50, 0 };
	m_vPoint[2]	   = { m_tInfo.vPos.x + 50, WINCY / 2 + 50, 0 };
	m_vPoint[3]	   = { m_tInfo.vPos.x - 50, WINCY / 2 + 50, 0 };
	m_tInfo.vLook  = { 0 , -1 , 0 };
	m_tInfo.vDir   = { 0 ,  1 , 0 };

	m_tItem = DIAMOND;
	CObj* Square = CAbstractFactory<CITemSquare>::Create_P(m_tInfo.vPos.x);
	m_vITemModel.push_back(Square);
	CObj* Triangle = CAbstractFactory<CITemTriangle>::Create_P(m_tInfo.vPos.x, WINCY / 2 -150);
	m_vITemModel.push_back(Triangle);
	m_fSpeed = 0.3f;
	
}

int CSlotItem::Update()
{
	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matTrans;

	for (int i = 0; i < 4; ++i)
	{

		D3DXVec3TransformCoord(&m_pItem[i], &m_pItem[i], &m_tInfo.matWorld);

	}


	for (size_t i =0; i< m_vITemModel.size(); ++i)
	{
		m_vITemModel[i]->Update();
	}
	return 0;
}

void CSlotItem::Late_Update()
{

	for (size_t i = 0; i < m_vITemModel.size(); ++i)
	{
		m_vITemModel[i]->Late_Update();
	}
}

void CSlotItem::Render(HDC hDC)
{


	for (size_t i = 0; i < m_vITemModel.size(); ++i)
	{
		m_vITemModel[i]->Render(hDC);
	}
	MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);
	
	for (int i = 0; i < 4; ++i)
		LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y);
	
	LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);
}

void CSlotItem::Release()
{
	for_each(m_vITemModel.begin(), m_vITemModel.end(), Safe_Delete<CObj*>);
}

void CSlotItem::ITemRender(ITEMMODEL tItem)
{
	switch (tItem)
	{
	case DIAMOND:
		break;
	case SQUARE:
		break;
	case TRIANGLE:
		break;
	case SEVEN:
		break;
	default:
		break;
	}
}
