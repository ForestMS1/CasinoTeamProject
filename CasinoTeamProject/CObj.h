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
	void Draw_Vertex(HDC hDC);

public:
	INFO			Get_Info()										{ return m_tInfo; }
	RENDERID		Get_RenderID() const							{ return m_eRender; }

	// 위치
	void			Set_Pos(float _x, float _y, float _z = 0.f)		{ m_tInfo.vPos.x = _x; m_tInfo.vPos.y = _y; m_tInfo.vPos.z = _z; }
	void			Set_Pos(D3DXVECTOR3 _vec)						{ m_tInfo.vPos = _vec; }
	void			Set_PosX(float _x)								{ m_tInfo.vPos.x = _x; }
	void			Set_PosY(float _y)								{ m_tInfo.vPos.y = _y; }
	void			Set_PosZ(float _z)								{ m_tInfo.vPos.z = _z; }

	// 크기
	void			Set_Scale(D3DXVECTOR3 _vScale)					{ m_tInfo.vScale = _vScale; }

	// 방향
	void			Set_Dir(D3DXVECTOR3 _vDir)						{ m_tInfo.vDir = _vDir; }

	bool			Is_Dead() const									{ return m_bIsDead; }
	void			Set_Dead()										{ m_bIsDead = true; }


protected:
	INFO		m_tInfo;
	float		m_fSpeed;

	//렌더순서
	RENDERID	m_eRender;

	// 생사 여부
	bool m_bIsDead;

	// 물체를 그릴 점 모아둘 vector
	vector<D3DXVECTOR3> m_vVertexes;
};

