#pragma once
#include "CObj.h"
class CPlayerL : public CObj
{
public:
	CPlayerL();
	virtual ~CPlayerL();

public:
	// CObj을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;


private:
	DWORD		m_dwChargeTime;
	
	float		m_fMinCharge;
	float		m_fMaxCharge;

	bool		m_bShot;
	bool		m_bJump;
	bool		m_bFalling;

	float		m_fAngle;
	INFO		m_tLine;

	D3DXVECTOR3  m_vCurrent;
};

