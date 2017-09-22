#include "stdafx.h"
#include "ROV.h"

CROV::CROV(void) : m_nErrno(ERR_NOTSUPPORTED)
{
}


CROV::~CROV(void)
{
}

bool CROV::UUV_Get( UUV_COMMAND strCommand, UUV_RESULT& pResult )
{
	m_nErrno = ERR_NOTSUPPORTED;
	return false;
}

bool CROV::UUV_Set( UUV_COMMAND strCommand, UUV_PARAM param )
{
	m_nErrno = ERR_NOTSUPPORTED;
	return false;
}

int CROV::UUV_GetErrno( void )
{
	return m_nErrno;
}

bool CROV::UUV_RegHandler( UUVHandler pHandler )
{
	m_nErrno = ERR_NOTSUPPORTED;
	return false;
}

bool CROV::UUV_RegVideoHandler( UUVVideoFrame pVideoHandler )
{
	m_nErrno = ERR_NOTSUPPORTED;
	return false;
}