#pragma once
#include "CObj.h"
#include <vector>
class CSlotItem :
    public CObj
{
private:
    enum ITEMMODEL{DIAMOND, SQUARE, TRIANGLE, SEVEN,MODEL_END};
public:
    CSlotItem();
    virtual ~CSlotItem();

public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    void ITemRender(ITEMMODEL tItem);

private:
    vector<CObj*>           m_vITemModel;
    ITEMMODEL               m_tItem;
    D3DXVECTOR3             m_pItem[4];

};

