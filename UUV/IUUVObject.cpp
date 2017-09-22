#include "stdafx.h"
#include "IUUVObject.h"
#include "ROVSharkMax.h"

IUUVObject* CreateUUV( E_UUV_TYPE type )
{
	IUUVObject* pUUV = nullptr;

	switch (type)
	{
	case E_ROV_SHARK_MAX:
		pUUV = new CROVSharkMax;
		break;
	default:
		break;
	}

	return pUUV;
}

void ReleaseUUV( IUUVObject* pUUV )
{
	if (pUUV)
	{
		delete pUUV;
		pUUV = nullptr;
	}
}
