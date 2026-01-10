#pragma once
#include "CObj.h"

template <typename T>
class CAbstractFactory
{
public:
	static CObj* Create_P(float fx = 0, float fy = 0)
	{
		CObj* pObj = new T;

		pObj->Set_PosX(fx);
		pObj->Set_PosY(fy);
		pObj->Initialize();
		return pObj;
	}
	static CObj* Create()
	{
		CObj* pObj = new T;
		pObj->Initialize();
		return pObj;
	}
	
};

