#pragma once
#include "CObj.h"
template<typename T>
class CAbstractFactory
{
public:
	static CObj* Create(float fX, float fY, float fZ)
	{
		CObj* pObj = new T;
		pObj->Set_Pos(fX, fY, fZ);
		pObj->Initialize();
		return pObj;
	}
};

