#include "pch.h"
#include "CSceneMgr.h"
#include "CScene.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;


CSceneMgr::CSceneMgr() : m_pCurScene(nullptr)
{

}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Initialize()
{
	m_pCurScene->Initialize();
}

int CSceneMgr::Update()
{
	m_pCurScene->Update();
	return 0;
}

void CSceneMgr::Late_Update()
{
	m_pCurScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	// 화면 지우기
	Rectangle(hDC, 0, 0, WINCX, WINCY);

	m_pCurScene->Render(hDC);
}

void CSceneMgr::Release()
{
	map<wstring, CScene*>::iterator iter = m_mapScene.begin();

	for (; iter != m_mapScene.end(); ++iter)
	{
		Safe_Delete(iter->second);
	}
	m_mapScene.clear();
}

void CSceneMgr::CreateScene(wstring sceneName, CScene* pScene)
{
	if (pScene != nullptr && (m_mapScene.find(sceneName) == m_mapScene.end()))
	{
		m_mapScene.insert({ sceneName, pScene });
	}
}

void CSceneMgr::ChangeScene(wstring sceneName)
{
	map<wstring, CScene*>::iterator iter = m_mapScene.find(sceneName);
	if (iter != m_mapScene.end())
	{
		if (m_pCurScene != nullptr)
			m_pCurScene->Release();

		m_pCurScene = iter->second;
		m_pCurScene->Initialize();
	}
}
