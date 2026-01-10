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

	CScene* GetCurScene()										{ return m_pCurScene; }
	CScene* FindScene(wstring sceneName)						{ return m_mapScene.find(sceneName)->second; }

private:
	CScene* m_pCurScene;
	map<wstring, CScene*> m_mapScene;
};

