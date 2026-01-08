#pragma once

#pragma region «ÿªÛµµ
#define WINCX 800
#define WINCY 600
#pragma endregion

#pragma region ΩÃ±€≈Ê ∏≈≈©∑Œ
#define SINGLE(T)							\
private:									\
T();										\
~T();										\
T& operator=(T&) = delete;					\
T(const T& rhs) = delete;					\
static T* m_pInstance;						\
											\
public:										\
	static T* Get_Instance()				\
	{										\
		if (m_pInstance == nullptr)			\
		{									\
			m_pInstance = new CSceneMgr;	\
		}									\
		return m_pInstance;					\
	}										\
											\
	static void Destroy_Instance()			\
	{										\
		if (m_pInstance)					\
		{									\
			delete m_pInstance;				\
			m_pInstance = nullptr;			\
		}									\
	}										
#pragma endregion
#define GETSINGLE(T) T::Get_Instance()
#define PURE = 0
#pragma region SafeDelete
template<typename T>
void Safe_Delete(T& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}
#pragma endregion

extern HWND g_hWnd;