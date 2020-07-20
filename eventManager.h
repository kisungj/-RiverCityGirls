#pragma once

#include "singletonBase.h"
class eventManager : public singletonBase<eventManager>
{
public:
	eventManager() {}
	~eventManager() {}

	HRESULT init();
	void release();
};

