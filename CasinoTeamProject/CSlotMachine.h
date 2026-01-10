#pragma once
#include "CObj.h"
class CSlotMachine : public CObj
{
public:
	CSlotMachine();
	virtual ~CSlotMachine();
private:
	// CObj을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

};

