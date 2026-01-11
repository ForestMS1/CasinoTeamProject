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
	float       m_fang;

	bool		m_bShot;
	bool		m_bJump;
	bool		m_bPullingCheck;
	bool		m_bCharging;
	bool		m_bFalling;
	bool		m_bLookCheck;
	bool        m_bSpinCheck;

	int			m_iAngleCount;

	float		m_fPosinSpeed;
	float		m_fPosinAngle;
	float		m_fAngle;
	float		m_fPower;
	float       m_ft;
	INFO		m_tLine;
	INFO		m_tPosin;
	
	D3DXVECTOR3  m_vCheckAngle[4];
	D3DXVECTOR3	 m_vSpin;

	D3DXVECTOR3  m_vPosin[2];
	D3DXVECTOR3  m_vPosinOriginal[2];
	D3DXVECTOR3  vLineCheck;
	D3DXVECTOR3  vLineOriginal;
};

