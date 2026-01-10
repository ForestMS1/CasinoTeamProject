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

	D3DXVECTOR3 Get_CardPos(int _index) 
	{ 
		if(_index < m_vecCardPosition.size())
			return m_vecCardPosition[_index];
	}
private:
	vector<D3DXVECTOR3> m_vecCardPosition;
};

