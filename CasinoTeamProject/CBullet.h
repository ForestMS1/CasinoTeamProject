#pragma once
#include "CObj.h"
class CBullet :
    public CObj
{
public:
    CBullet();
    ~CBullet();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    void Set_MatRotate(D3DXMATRIX _matRotate) { m_matRotate = _matRotate; }
private:
    D3DXMATRIX m_matRotate; // 총과 공유하는 회전 행렬
};

