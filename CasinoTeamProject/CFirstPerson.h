#pragma once
#include "CObj.h"
class CFirstPerson : public CObj
{
public:
	CFirstPerson();
	virtual ~CFirstPerson();

	// CObj을(를) 통해 상속됨
public:	
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

