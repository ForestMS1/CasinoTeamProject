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
	D3DXVECTOR3*	Get_PointInfo()							{ return m_vPoint; }
	RENDERID		Get_RenderID() const					{ return m_eRender; }
	bool			Get_Jump()								{ return m_bJump; }
	bool			Get_LineCheck()							{ return m_bLineCheck; }
	void			Set_PosX(float _x)						{ m_tInfo.vPos.x = _x; }
	void			Set_PosY(float _y)						{ m_tInfo.vPos.y = _y; }
	bool			Is_Dead() const							{ return m_bIsDead; }
	void			Set_Dead()								{ m_bIsDead = true; }
	void			Set_Hit()								{ m_bHit = true; }
	void			Set_Score()								{ m_bScore = true; }

protected:

	D3DXVECTOR3 m_vOriginal[4];
	D3DXVECTOR3 m_vPoint[4];
	
	//정점 보정
	D3DXVECTOR3 m_vPos;   
	
	INFO		m_tInfo;
	
	
	float		m_fSpeed;
	float		m_fScale;


	//렌더순서
	RENDERID	m_eRender;

	// 생사 여부
	bool m_bIsDead;
	// 플레이어 충돌 체크
	bool		 m_bHit;
	bool		 m_bScore;    //점수 체크
	bool		 m_bLineCheck; //줄넘기 라인 충돌 체크
	bool		 m_bJump;      //점프 체크
};

