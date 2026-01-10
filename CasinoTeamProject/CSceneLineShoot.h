#pragma once
#include "CScene.h"
class CSceneLineShoot : public CScene
{
public:
	CSceneLineShoot();
	virtual ~CSceneLineShoot();

public:
	// CScene을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

