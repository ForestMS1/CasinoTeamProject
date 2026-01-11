#pragma once
#include "CObj.h"

class CPosinShoot : public CObj
{
public:
	CPosinShoot();
	virtual ~CPosinShoot();

public:
	// CObj을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	vector<D3DXVECTOR3>  m_vecPoint[60];

	vector<D3DXVECTOR3>  m_vecOrignal[60];
	vector<D3DXMATRIX>  m_vecMat;

	D3DXVECTOR3 m_vPOne[4];
	D3DXVECTOR3 m_vPTwo[4];
};

