#pragma once
#include "CObj.h"
class CRopeDot : public CObj
{
public:
	CRopeDot();
	~CRopeDot();
public:
	

	// CObj을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC hDC) override;

	void Release() override;

};

