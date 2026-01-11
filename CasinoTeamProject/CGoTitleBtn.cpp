#include "pch.h"
#include "CGoTitleBtn.h"
#include "CKeyMgr.h"
CGoTitleBtn::CGoTitleBtn() : m_bNextScene(false)
{
	m_eRender = GAMEOBJECT;
}

CGoTitleBtn::~CGoTitleBtn()
{
	Release();
}

void CGoTitleBtn::Initialize()
{
	m_tInfo.vPos = { 25.f, 25.f, 0.f };
	m_tInfo.vScale = { 50.f, 50.f, 0.f };
	float fHalfX = m_tInfo.vScale.x * 0.5f;
	float fHalfY = m_tInfo.vScale.y * 0.5f;


#pragma region 뒤로가기 버튼
	m_vVertexes.push_back({ m_tInfo.vPos.x + fHalfX, m_tInfo.vPos.y - fHalfY, 0.f });
	m_vVertexes.push_back({ m_tInfo.vPos.x - fHalfX, m_tInfo.vPos.y - fHalfY, 0.f });
	m_vVertexes.push_back({ m_tInfo.vPos.x - fHalfX, m_tInfo.vPos.y + fHalfY, 0.f });
	m_vVertexes.push_back({ m_tInfo.vPos.x + fHalfX, m_tInfo.vPos.y + fHalfY, 0.f });
	m_vVertexes.push_back({ m_tInfo.vPos.x + fHalfX, m_tInfo.vPos.y - fHalfY, 0.f });


	//화살표
	m_vVertexes.push_back({ m_tInfo.vPos.x + fHalfX, m_tInfo.vPos.y, 0.f });
	m_vVertexes.push_back({ m_tInfo.vPos.x - fHalfX, m_tInfo.vPos.y , 0.f });
	m_vVertexes.push_back({ m_tInfo.vPos.x - fHalfX * 0.5f, m_tInfo.vPos.y - fHalfY, 0.f });
	m_vVertexes.push_back({ m_tInfo.vPos.x - fHalfX * 0.5f, m_tInfo.vPos.y + fHalfY, 0.f });
	m_vVertexes.push_back({ m_tInfo.vPos.x - fHalfX, m_tInfo.vPos.y , 0.f });
	m_vVertexes.push_back({ m_tInfo.vPos.x + fHalfX, m_tInfo.vPos.y, 0.f });
#pragma endregion

	m_tRect.left = m_tInfo.vPos.x - fHalfX;
	m_tRect.top = m_tInfo.vPos.y - fHalfY;
	m_tRect.right = m_tInfo.vPos.x + fHalfX;
	m_tRect.bottom = m_tInfo.vPos.y + fHalfY;
}

int CGoTitleBtn::Update()
{
	POINT ptMouse = { (int)Get_Mouse().x, (int)Get_Mouse().y };
	if (PtInRect(&m_tRect, ptMouse))
	{
		if (GETSINGLE(CKeyMgr)->Key_Pressing(VK_LBUTTON) && !m_bNextScene)
		{
			m_bNextScene = true;
		}
	}
	return 0;
}

void CGoTitleBtn::Late_Update()
{
}

void CGoTitleBtn::Render(HDC hDC)
{
	__super::Draw_Vertex(hDC);
}

void CGoTitleBtn::Release()
{
}
