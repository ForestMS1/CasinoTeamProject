#pragma once
#include "CObj.h"
class CPlayerR : public CObj
{
public:
	CPlayerR();
	virtual ~CPlayerR();
public:

	// CObj을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void Key_Input();
	void Jump_Check();
	void Falling_Check();
	void Hitttttttt();
	int Get_Score() { return m_iScore; }
	bool Line_Check();

private:

	
	float		 m_fMaxJump;
	float		 m_fMaxCheck;
	float		 m_fCheckScale;
	FLOAT		 m_fY;
	float		 m_fBack;
	float		 m_fT;
	float		 m_fHitY;
	float		 m_fHitTime;

	int			 m_iScore;

	bool		 m_bFalling;

	DWORD		 m_dwHitTIme;
	D3DXVECTOR3  m_vCurrentPos;
	D3DXVECTOR3	 m_vScale;
};

