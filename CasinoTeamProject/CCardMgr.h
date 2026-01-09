#pragma once
#include "Define.h"
#include "CCard.h"
class CCardMgr
{
	SINGLE(CCardMgr)
public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();
private:
	vector<CCard*> m_vecCardPosition;
};

