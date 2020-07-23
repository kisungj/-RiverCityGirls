#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"

HRESULT enemyManager::init()
{
	return S_OK;
}

void enemyManager::render()
{
	for (int i = 0; i < _vBoy.size(); i++)
	{
		_vBoy[i]->render();
	}

	for (int i = 0; i < _vGirl.size(); i++)
	{
		_vGirl[i]->render();
	}
}

void enemyManager::update()
{
	for (int i = 0; i < _vBoy.size(); i++)
	{
		_vBoy[i]->update();
		_vBoy[i]->directionCheck(_player->getPlayerRect(), _player->getPlayerX(), _player->getShadowY());
	}

	for (int i = 0; i < _vGirl.size(); i++)
	{
		_vGirl[i]->update();
		_vGirl[i]->directionCheck(_player->getPlayerRect(), _player->getPlayerX(), _player->getShadowY());
	}
}

void enemyManager::release()
{
	for (int i = 0; i < _vBoy.size(); i++)
	{
		SAFE_DELETE(_vBoy[i]);
	}

	for (int i = 0; i < _vGirl.size(); i++)
	{
		SAFE_DELETE(_vGirl[i]);
	}

	_vBoy.clear();
	_vGirl.clear();
}

void enemyManager::setBoy()
{
	for (int i = 0; i < 1; ++i)
	{
		enemy* boy;
		boy = new enemyBoy;
		boy->init(300, WINSIZEY / 2 + 300, ENEMYTYPE::BOY);

		_vBoy.push_back(boy);
	}

	for (int i = 0; i < 2; ++i)
	{
		enemy* girl;
		girl = new enemyGirl;
		girl->init(2000 + i * 100, (WINSIZEY / 2 + 200) + i * 200, ENEMYTYPE::GIRL);

		_vGirl.push_back(girl);
	}
}

void enemyManager::setGirl()
{

	for (int i = 0; i < 2; ++i)
	{
		enemy* girl;
		girl = new enemyGirl;
		girl->init(2000 + i * 100, (WINSIZEY / 2 + 200) + i * 200, ENEMYTYPE::GIRL);

		_vGirl.push_back(girl);
	}
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
	_vGirl.erase(_vGirl.begin() + arrNum);
}

void enemyManager::eraseCheer(int arrNum)
{
}

