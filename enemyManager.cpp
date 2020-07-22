#include "stdafx.h"
#include "enemyManager.h"

HRESULT enemyManager::init()
{

	return S_OK;
}

void enemyManager::render()
{
	
}

void enemyManager::update()
{
}

void enemyManager::release()
{
}

void enemyManager::setBoy()
{
	for (int i = 0; i < 1; ++i)
	{
		enemy* boy;
		boy = new enemyBoy;
		boy->init(1000, WINSIZEY / 2 + 300);

		_vBoy.push_back(boy);
	}
}

void enemyManager::setGirl()
{
}

void enemyManager::setCheer()
{
}

void enemyManager::eraseBoy(int arrNum)
{
	_vBoy.erase(_vBoy.begin() + arrNum);
}

void enemyManager::eraseGirl(int arrNum)
{
}

void enemyManager::eraseCheer(int arrNum)
{
}
