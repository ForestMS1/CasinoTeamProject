#include "pch.h"
#include "CCardMgr.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
CCardMgr* CCardMgr::m_pInstance = nullptr;


CCardMgr::CCardMgr()
{

}

CCardMgr::~CCardMgr()
{
	Release();
}

void CCardMgr::Initialize()
{
	float fStartPosX = 100.f;
	float fStartPosY = 100.f;
	// 행 간격
	float fDistRow = 200.f;
	// 열 간격
	float fDistCol = 120.f;

	// 카드가 배치될 pos를 저장
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			m_vecCardPosition.push_back(D3DXVECTOR3(fStartPosX + j * fDistCol, fStartPosY + i * fDistRow, 0.f));
		}
	}

	for (int i = 0; i < 18; ++i)
	{
		CCard* pCard = new CCard(CCard::CARDTYPE(i / 2));
		pCard->Set_Pos(WINCX, WINCY, 0.f);
		pCard->Initialize();
		GETSINGLE(CObjMgr)->AddObject(OBJ_ITEM, pCard);
		//GETSINGLE(CObjMgr)->AddObject(OBJ_ITEM, CAbstractFactory<CCard>::Create(D3DXVECTOR3(WINCX, WINCY, 0.f)));
	}

	m_pDeterminingCard.first = nullptr;
	m_pDeterminingCard.second = nullptr;
}

void CCardMgr::Update()
{

}

void CCardMgr::Late_Update()
{

}

void CCardMgr::Render(HDC hDC)
{
	//for (auto& cardPos : m_vecCardPosition)
	//{
	//	SetPixel(hDC, cardPos.x, cardPos.y, RGB(255,0,0));
	//}

}

void CCardMgr::Release()
{

}

bool CCardMgr::IsPair()
{
	if (m_pDeterminingCard.first != nullptr && m_pDeterminingCard.second != nullptr)
	{
		if (m_pDeterminingCard.first->Get_Type() == m_pDeterminingCard.second->Get_Type())
		{
			m_pDeterminingCard.first = nullptr;
			m_pDeterminingCard.second = nullptr;
			m_iPairCnt++;
			return true;
		}
		else
		{
			m_pDeterminingCard.first->Card_Open(false);
			m_pDeterminingCard.second->Card_Open(false);
			m_pDeterminingCard.first = nullptr;
			m_pDeterminingCard.second = nullptr;
			return false;
		}
	}
	return false;
}
