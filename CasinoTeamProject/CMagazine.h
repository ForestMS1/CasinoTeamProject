#pragma once
#include "CObj.h"
class CMagazine :
    public CObj
{
public:
    CMagazine();
    ~CMagazine();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    void Set_Angle(float _angle)                { m_fAngle = _angle; }

private:
    void Rotate();

private:
    float m_fAngle;
};

