#pragma once
#include "CObj.h"
class CCard :
    public CObj
{
public:
    enum CARDTYPE { HEART, SPADE, CLOVER, TYPE_END};
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
    bool            m_bIsOpen;  // false면 뒷면, true면 앞면
    int             m_iIndex;   // 카드덱에서의 인덱스
    CARDTYPE        m_eType;    // 그림

};

