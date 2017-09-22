#pragma once


class CROV : public IUUVObject
{
public:
	CROV(void);
	virtual ~CROV(void);

	virtual bool UUV_RegHandler(UUVHandler pHandler);
	virtual bool UUV_RegVideoHandler(UUVVideoFrame pVideoHandler);
	virtual bool UUV_Get(UUV_COMMAND strCommand, UUV_RESULT& pResult);
	virtual bool UUV_Set(UUV_COMMAND strCommand, UUV_PARAM	param);

public:
	int UUV_GetErrno(void);

protected:
	int m_nErrno;
};

