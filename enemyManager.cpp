#include "stdafx.h"
#include "enemyManager.h"

HRESULT enemyManager::init()
{
	_boy = new enemyBoy;
	_boy->init();

	return S_OK;
}

void enemyManager::render()
{
	_boy->render();
}

void enemyManager::update()
{
	_boy->update();
}

void enemyManager::release()
{
	_boy->release();
}
