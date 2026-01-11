#pragma once
#include "CObj.h"
class CLineShoot : public CObj
{
public:
	CLineShoot();
	virtual ~CLineShoot();

public:
	// CObj을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
public:
	bool	Get_Click() { return m_bClick; }
	bool	Get_Pull() { return m_bPull; }
public:
	void	Key_Input();
private:
	D3DXVECTOR3 m_vCurLinePos;
	bool	m_bClick;
	bool	m_bPull;
};

