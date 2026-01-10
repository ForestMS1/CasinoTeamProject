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
	bool			Is_Dead() const							{ return m_bIsDead; }
	void			Set_Dead()								{ m_bIsDead = true; }
	void			Set_Hit()								{ m_bHit = true; }
	void			Set_Score()								{ m_bScore = true; }
	void Draw_Vertex(HDC hDC);
	void Draw_Vertex_Color(HDC hDC, float _r, float _g, float _b);
public:

	// ��ġ
	void			Set_Pos(float _x, float _y, float _z = 0.f)		{ m_tInfo.vPos.x = _x; m_tInfo.vPos.y = _y; m_tInfo.vPos.z = _z; }
	void			Set_Pos(D3DXVECTOR3 _vec)						{ m_tInfo.vPos = _vec; }
	void			Set_PosX(float _x)								{ m_tInfo.vPos.x = _x; }
	void			Set_PosY(float _y)								{ m_tInfo.vPos.y = _y; }
	void			Set_PosZ(float _z)								{ m_tInfo.vPos.z = _z; }

	// ũ��
	void			Set_Scale(D3DXVECTOR3 _vScale)					{ m_tInfo.vScale = _vScale; }

	// ����
	void			Set_Dir(D3DXVECTOR3 _vDir)						{ m_tInfo.vDir = _vDir; }


protected:

	D3DXVECTOR3 m_vOriginal[4];
	D3DXVECTOR3 m_vPoint[4];
	
	//���� ����
	D3DXVECTOR3 m_vPos;   
	
	INFO		m_tInfo;
	
	
	float		m_fSpeed;
	float		m_fScale;

	float	  m_fAngle;

	//��������
	RENDERID	m_eRender;

	// ���� ����
	bool m_bIsDead;
	// �÷��̾� �浹 üũ
	bool		 m_bHit;
	bool		 m_bScore;    //���� üũ
	bool		 m_bLineCheck; //�ٳѱ� ���� �浹 üũ
	bool		 m_bJump;      //���� üũ

	// ��ü�� �׸� �� ��Ƶ� vector
	vector<D3DXVECTOR3> m_vVertexes;
};

