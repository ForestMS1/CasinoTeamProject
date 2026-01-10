#include "pch.h"
#include "CObj.h"

CObj::CObj() : 
	m_bIsDead(false), 
	m_fSpeed(0.f),
	m_eRender(RENDER_END),
	m_bScore(false),
	m_bJump(false)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	D3DXMatrixIdentity(&m_tInfo.matWorld);
}

CObj::~CObj()
{
}

void CObj::Draw_Vertex(HDC hDC)
{
	if (m_vVertexes.empty())
		return;

	MoveToEx(hDC, m_vVertexes[0].x, m_vVertexes[0].y, nullptr);
	for (auto& vertex : m_vVertexes)
	{
		LineTo(hDC, vertex.x, vertex.y);
	}
	LineTo(hDC, m_vVertexes[0].x, m_vVertexes[0].y);
}

void CObj::Draw_Vertex_Color(HDC hDC, float _r, float _g, float _b)
{
	if (m_vVertexes.empty())
		return;

	HPEN hPen = CreatePen(0, 5, RGB(_r, _g, _b));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

	MoveToEx(hDC, m_vVertexes[0].x, m_vVertexes[0].y, nullptr);
	for (auto& vertex : m_vVertexes)
	{
		LineTo(hDC, vertex.x, vertex.y);
	}
	LineTo(hDC, m_vVertexes[0].x, m_vVertexes[0].y);

	hPen = (HPEN)SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
}
