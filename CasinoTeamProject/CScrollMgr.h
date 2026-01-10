#pragma once

#include "Define.h"

class CScrollMgr
{
private:
	CScrollMgr();
	CScrollMgr& operator=(CScrollMgr&) = delete;
	CScrollMgr(const CScrollMgr& rhs) = delete;
	~CScrollMgr();


public:
	float			Get_ScrollX() { return m_fScrollX; }
	float			Get_ScrollY() { return m_fScrollY; }
	D3DXVECTOR3		Get_VInfo() { return m_vtInfo; }
	void			Set_ScrollX(float fX) { m_fScrollX += fX; }
	void			Set_ScrollY(float fY) { m_fScrollY += fY; }
	void			ReSet_SrollY() { m_fScrollY = 0; }
	void			Set_VInfo(D3DXVECTOR3 vt) { m_vtInfo = vt; }
	void			Scroll_Lock();

	void			Set_Limit(float fx, float fy) { m_fLimitX = fx, m_fLimitY = fy; }

public:
	static CScrollMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CScrollMgr;

		return m_pInstance;
	}

	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CScrollMgr* m_pInstance;

	D3DXVECTOR3			m_vtInfo;
	float				m_fScrollX;
	float				m_fScrollY;
	float				m_fLimitX;
	float				m_fLimitY;

};

