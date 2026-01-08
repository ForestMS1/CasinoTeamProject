#pragma once
#include "CScene.h"
class CTitleScene :
    public CScene
{
public:
    CTitleScene();
    ~CTitleScene();

public:
    // CScene을(를) 통해 상속됨
    void Initialize() override;

    int Update() override;

    void Late_Update() override;

    void Render(HDC hDC) override;

    void Release() override;

};

