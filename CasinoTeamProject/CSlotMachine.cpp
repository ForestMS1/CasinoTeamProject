#include "pch.h"
#include "CSlotMachine.h"
#include "CSlotItem.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CScrollMgr.h"
CSlotMachine::CSlotMachine()
{
	m_eRender = GAMEOBJECT;
}

CSlotMachine::~CSlotMachine()
{
}

void CSlotMachine::Initialize()
{

	m_vPoint[0] = {WINCX / 16 - 25, WINCY / 2 - 50, 0};
	m_vPoint[1] = {WINCX / 16 + 25, WINCY / 2 - 50, 0 };
	m_vPoint[2] = {WINCX / 16 + 25, WINCY / 2 + 50, 0 };
	m_vPoint[3] = {WINCX / 16 - 25, WINCY / 2 + 50, 0 };
	m_tInfo.vPos = { WINCX / 2, WINCY / 2 , 0.f };

}

int CSlotMachine::Update()
{
	
	return 0;
}

void CSlotMachine::Late_Update()
{
}

void CSlotMachine::Render(HDC hDC)
{
	MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);

	for (int i = 0; i < 4; ++i)
		LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y);

	LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);
}

void CSlotMachine::Release()
{

	GETSINGLE(CObjMgr)->DeleteLayerObj(OBJ_SLOTITEM);
}
