#pragma once
#include "CObj.h"
class CCard :
    public CObj
{
public:
    enum CARDTYPE { HEART, SPADE, CLOVER, TYPE_END };
public:
    CCard();
    ~CCard();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    void Card_Open(bool _isOpen)                { m_bIsOpen = _isOpen; }
    void Set_Index(int _index)                  { m_iIndex = _index; }

private:
    bool                        m_bIsOpen;  // false면 뒷면, true면 앞면
    CARDTYPE                    m_eType;    // 그림
    int                         m_iIndex;
    D3DXVECTOR3                 m_dvPos;    // 카드가 배치될 자리
public:
    static int             _sCardCnt;   // 총 카드 수
};

