#pragma once
#include "CObj.h"
class CGoTitleBtn :
    public CObj
{
public:
    CGoTitleBtn();
    ~CGoTitleBtn();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    bool ChangeNextScene()  const { return m_bNextScene; }

private:
    RECT m_tRect;
    bool m_bNextScene;
};

