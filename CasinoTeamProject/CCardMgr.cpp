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
	float fDistCol = 200.f;

	// 카드가 배치될 pos를 저장
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			m_vecCardPosition.push_back(D3DXVECTOR3(fStartPosX + j * fDistCol, fStartPosY + i * fDistRow, 0.f));
		}
	}
}

void CCardMgr::Update()
{

}

void CCardMgr::Late_Update()
{

}

void CCardMgr::Render(HDC hDC)
{
	for (auto& cardPos : m_vecCardPosition)
	{
		SetPixel(hDC, cardPos.x, cardPos.y, RGB(255,0,0));
	}

}

void CCardMgr::Release()
{

}
