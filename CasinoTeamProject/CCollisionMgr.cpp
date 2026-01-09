#include "pch.h"
#include "CCollisionMgr.h"


void CCollisionMgr::Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src)
{
	float	fWidth(0.f), fHeight(0.f);

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Rect(Dst, Src, &fWidth, &fHeight))
			{
				// 상 하 충돌
				if (fWidth > fHeight)
				{
					// 상 충돌
					if (Dst->Get_Info().vPos.y < Src->Get_Info().vPos.y)
					{
						Dst->Set_PosY(-fHeight);
					}
					// 하 충돌
					else
					{
						Dst->Set_PosY(fHeight);
					}
				}

				// 좌 우 충돌
				else
				{
					// 좌 충돌
					if (Dst->Get_Info().vPos.x < Src->Get_Info().vPos.x)
					{
						Dst->Set_PosX(-fWidth);
					}
					// 우 충돌
					else
					{
						Dst->Set_PosX(fWidth);
					}
				}
			}
		}
	}
}


bool CCollisionMgr::Check_Rect(CObj* pDst, CObj* pSrc, float* pX, float* pY)
{
	float		fWidth = fabsf(pDst->Get_Info().vPos.x - pSrc->Get_Info().vPos.x);
	float		fHeight = fabsf(pDst->Get_Info().vPos.y - pSrc->Get_Info().vPos.y);

	float		fRadiusX = (pDst->Get_Info().vScale.x + pSrc->Get_Info().vScale.x) * 0.5f;
	float		fRadiusY = (pDst->Get_Info().vScale.y + pSrc->Get_Info().vScale.y) * 0.5f;

	if (fRadiusX >= fWidth && fRadiusY >= fHeight)
	{
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;

		return true;
	}

	return false;
}

bool CCollisionMgr::Check_Circle(CObj* pDst, CObj* pSrc)
{
	float	fRadius = (pDst->Get_Info().vScale.x + pSrc->Get_Info().vScale.x) * 0.5f;

	float	fWidth = fabsf(pDst->Get_Info().vPos.x - pSrc->Get_Info().vPos.x);
	float	fHeight = fabsf(pDst->Get_Info().vPos.y - pSrc->Get_Info().vPos.y);

	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	return fRadius >= fDiagonal;
}

void CCollisionMgr::Collision_Circle(list<CObj*> _Dst, list<CObj*> _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Circle(Dst, Src))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}
