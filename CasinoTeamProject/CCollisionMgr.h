#pragma once

#include "CObj.h"

class CWeapon;
class CCollisionMgr
{
public:
	static void Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src);
	static bool	Check_Rect(CObj* pDst, CObj* pSrc, float* pX, float* pY);
	static bool Check_Circle(CObj* pDst, CObj* pSrc);
	static void Collision_Circle(list<CObj*> _Dst, list<CObj*> _Src);
	static void Collision_Rope(CObj* pDst, CObj* pSrc);
	// 충돌처리는 필요하면 마음대로 추가
	static void	Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src);
};


