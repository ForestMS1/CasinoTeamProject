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

	float		fRadiusX = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
	float		fRadiusY = (pDst->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.5f;

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
	float	fRadius = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;

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

void CCollisionMgr::Collision_Rope(CObj* pDst, CObj* pSrc)
{
	float fPlayerYCheck(0.f), fRopeYCheck(0.f), fPlayerDistance(0.f), fRopeDistance(0.f);
	D3DXMATRIX  matRopeWorld;
	D3DXVECTOR3 vRope, vOriginRope;
	
	//Rope의 vector값을 담기 위함
	ZeroMemory(&vRope, sizeof(vRope));
	ZeroMemory(&vOriginRope, sizeof(vOriginRope));

	//Rope 원점 돌리기
	vOriginRope = { 0.f , WINCY / 2,0.f };
	vOriginRope -= { 0.f ,WINCY - WINCY / 2 - 50 ,0.f};

	//Rope X축 반영된 월드 좌표 가져오기
	matRopeWorld = pDst->Get_Info().matWorld;
	
	//슛
	D3DXVec3TransformCoord(&vRope,  &vOriginRope,  &matRopeWorld);

	//Player는 로컬 좌표로
	fPlayerYCheck = pSrc->Get_Info().vPos.y;
	fRopeYCheck =   vRope.y;

	//대충 보정 값 때려 맞추기
	fPlayerDistance = fabsf(fPlayerYCheck - (WINCY / 2 + 25) );
	fRopeDistance   = fabsf(fRopeYCheck   - (WINCY / 2 + 45) );
	
	//일점 범위 높이 편차값으로 Player 밀어내기
	if (fRopeDistance <= 10 && fPlayerDistance <= fRopeDistance && pSrc->Get_LineCheck())
		pSrc->Set_Hit();

	//줄 넘으면 점수추가
	if (fRopeDistance <= 10 && pSrc->Get_Jump())
		pSrc->Set_Score();
}
