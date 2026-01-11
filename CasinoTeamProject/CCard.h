#pragma once
#include "CObj.h"
class CCard :
    public CObj
{
public:
    enum CARDTYPE { HEART_1, HEART_2, HEART_3, SPADE_1, SPADE_2, SPADE_3, CLOVER_1, CLOVER_2, CLOVER_3, TYPE_END };
public:
    CCard();
    CCard(CARDTYPE _type);
    ~CCard();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    void Card_Open(bool _isOpen)                
    { 
        m_bIsOpen = _isOpen; 
        //if(_isOpen == false)
           // m_bFlipComplete = false; 
    }
    void Set_Index(int _index)                  { m_iIndex = _index; }
    CARDTYPE Get_Type() const                   { return m_eType; }

private:
    bool                        m_bIsOpen;  // false면 뒷면, true면 앞면
    CARDTYPE                    m_eType;    // 그림
    int                         m_iIndex;
    D3DXVECTOR3                 m_dvPos;    // 카드가 배치될 자리
    bool                        m_bFlipComplete; // 다 뒤집어졌는지
    float                       m_fFlipAngle;

    RECT                        m_tRect;    // 충돌 사각형

    vector<D3DXVECTOR3>         m_dvEmblemVertex;
public:
    static int             _sCardCnt;   // 총 카드 수
};

