#pragma once
#include "CObj.h"
class CRevolver :
    public CObj
{
public:
    CRevolver();
    ~CRevolver();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    void Rotate_Muzzle();
    void Shot();
private:
    D3DXVECTOR3 m_vecMuzzle;
    float m_fAngle;
    int m_iBullet;

    D3DXMATRIX m_matRotate; // 총알과 공유 할 회전 행렬
};

