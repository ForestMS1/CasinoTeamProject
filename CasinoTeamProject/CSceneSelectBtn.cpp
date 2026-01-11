#include "pch.h"
#include "CSceneSelectBtn.h"
#include "CKeyMgr.h"
CSceneSelectBtn::CSceneSelectBtn() : m_bNextScene(false)
{
	m_eRender = GAMEOBJECT;
	m_wsNextSceneName = L"";
}

CSceneSelectBtn::CSceneSelectBtn(wstring _nextSceneName) : m_bNextScene(false)
{
	m_eRender = GAMEOBJECT;
	m_wsNextSceneName = _nextSceneName;
}

CSceneSelectBtn::~CSceneSelectBtn()
{
	Release();
}

void CSceneSelectBtn::Initialize()
{
	//m_tInfo.vPos = { 400, 300, 0 };
	m_tInfo.vScale = { 50.f, 50.f, 0.f };

	float fHalfX = m_tInfo.vScale.x * 0.5f;
	float fHalfY = m_tInfo.vScale.y * 0.5f;

	m_tRect.left = m_tInfo.vPos.x - fHalfX;
	m_tRect.top = m_tInfo.vPos.y - fHalfY;
	m_tRect.right = m_tInfo.vPos.x + fHalfX;
	m_tRect.bottom = m_tInfo.vPos.y + fHalfY;
}

int CSceneSelectBtn::Update()
{
	POINT ptMouse = { Get_Mouse().x, Get_Mouse().y };
	if (PtInRect(&m_tRect, ptMouse))
	{
		if (GETSINGLE(CKeyMgr)->Key_Pressing(VK_LBUTTON) && !m_bNextScene)
		{
			m_bNextScene = true;
		}
	}
	return 0;
}

void CSceneSelectBtn::Late_Update()
{
}

void CSceneSelectBtn::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	TextOutW(hDC, m_tRect.left, m_tRect.top, m_wsNextSceneName.c_str(), m_wsNextSceneName.size());
}

void CSceneSelectBtn::Release()
{
}
