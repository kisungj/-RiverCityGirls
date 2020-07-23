#pragma once
#include "singletonBase.h"

class zOrderManager : public singletonBase<zOrderManager>
{
private:

public:
	zOrderManager() {}
	~zOrderManager() {}

public:
	HRESULT init();
	void release();

};

