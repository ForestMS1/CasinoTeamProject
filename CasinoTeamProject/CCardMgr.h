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

	bool IsPair();
	void Set_DeterminingCard(CCard* _card)
	{
		if (m_pDeterminingCard.first == nullptr)
		{
			m_pDeterminingCard.first = _card;
		}
		else
		{
			m_pDeterminingCard.second = _card;
		}
	}
	bool Game_Clear()				{ return m_iMaxPairCnt == m_iPairCnt; }
	
private:
	vector<D3DXVECTOR3> m_vecCardPosition;
	pair<CCard*, CCard*> m_pDeterminingCard;
	const int m_iMaxPairCnt = 9;
	int		  m_iPairCnt = 0;
};

