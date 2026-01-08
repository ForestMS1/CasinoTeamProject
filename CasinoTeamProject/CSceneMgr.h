#pragma once
#include "CScene.h"
class CSceneMgr
{
	SINGLE(CSceneMgr)
public:
	void Initialize();
	int	 Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

public:
	void CreateScene(wstring sceneName, CScene* pScene);
	void ChangeScene(wstring sceneName);

private:
	CScene* m_pCurScene;
	map<wstring, CScene*> m_mapScene;
};

