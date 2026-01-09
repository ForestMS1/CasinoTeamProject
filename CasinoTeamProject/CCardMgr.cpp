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
	
}

void CCardMgr::Update()
{

}

void CCardMgr::Late_Update()
{

}

void CCardMgr::Render(HDC hDC)
{
	// Ä«µå µ¦ ¹¶Ä¡

}

void CCardMgr::Release()
{

}
