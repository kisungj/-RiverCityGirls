#include "stdafx.h"
#include "stageBoss.h"
HRESULT stageBoss::init()
{
	_boss = new boss;
	_boss->init();

	return S_OK;
}

void stageBoss::render()
{
	_boss->render();
}

void stageBoss::update()
{
	_boss->update();
}

void stageBoss::release()
{
	_boss->release();
}
