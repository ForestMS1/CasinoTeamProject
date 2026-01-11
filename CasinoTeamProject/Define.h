#pragma once

#pragma region 해상도
#define WINCX 800
#define WINCY 600
#pragma endregion

#pragma region 싱글톤 매크로
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
			m_pInstance = new T;			\
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
#define	OBJ_NOEVENT 0
#define	OBJ_DEAD    1
#define VK_MAX		0xff
enum OBJ_LAYER { OBJ_PLAYER, OBJ_EFFECT, OBJ_ITEM, OBJ_ROLLING, OBJ_ROPE, OBJ_LINE, OBJ_BACK_BUTTON, OBJ_END };
#define PI				3.14159265358979
//#define TO_RADIAN(D)	D * 180.f/PI
//#define TO_DEGREE(R)	R * PI/180.f
enum RENDERID { BACK, GAMEOBJECT, BULLET, PLAYER, EFFECT, UI, RENDER_END };
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

typedef struct tagInfo
{
	D3DXVECTOR3		vPos;		// 위치 벡터
	D3DXVECTOR3		vDir;		// 방향 벡터

	D3DXVECTOR3		vLook;
	D3DXVECTOR3		vNormal;	// 법선 벡터

	// 객체의 크기
	D3DXVECTOR3		vScale;
	//float			fCX;
	//float			fCY;
	//float			fCZ;

	D3DXMATRIX		matWorld;

}INFO;

typedef struct tagLinePoint
{
	float		fX;
	float		fY;

	tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}

}LINEPOINT;

extern HWND g_hWnd;


static D3DXVECTOR3	Get_Mouse()
{
	POINT		ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	return { (float)ptMouse.x, (float)ptMouse.y, 0.f };
}
