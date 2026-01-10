#pragma once
#include "CObj.h"
class CRope : public CObj
{
public:
	CRope();
	virtual ~CRope();
public:
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC hDC) override;

	void Release() override;

private:
	D3DXVECTOR3     m_vScale;
	D3DXVECTOR3		m_RopePoint[9];
	D3DXVECTOR3		m_RopeOriginal[9];
	float m_fAngle;
	bool  m_bCheck;
	float m_MaxY;
	float m_MinY;


	wchar_t			 m_sZScore[32];
};

