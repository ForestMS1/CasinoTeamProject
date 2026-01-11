#pragma once
#include "CObj.h"
class CSceneSelectBtn :
    public CObj
{
public:
    CSceneSelectBtn();
    CSceneSelectBtn(wstring _nextSceneName);
    ~CSceneSelectBtn();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    wstring Get_NextSceneName() const { return m_wsNextSceneName; }
    bool ChangeNextScene()  const { return m_bNextScene; }

private:
    RECT m_tRect;
    wstring m_wsNextSceneName;
    bool m_bNextScene;
};

