#pragma once
#include "Define.h"
class CObj abstract
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize()							PURE;
	virtual int Update()								PURE;
	virtual void Late_Update()							PURE;
	virtual void Render(HDC hDC)						PURE;
	virtual void Release()								PURE;

public:
	INFO			Get_Info()								{ return m_tInfo; }
	RENDERID		Get_RenderID() const					{ return m_eRender; }
	
	void			Set_PosX(float _x)						{ m_tInfo.vPos.x = _x; }
	void			Set_PosY(float _y)						{ m_tInfo.vPos.y = _y; }
	bool			Is_Dead() const							{ return m_bIsDead; }
	void			Set_Dead()								{ m_bIsDead = true; }


protected:
	INFO		m_tInfo;
	float		m_fSpeed;

	//렌더순서
	RENDERID	m_eRender;

	// 생사 여부
	bool m_bIsDead;
};

