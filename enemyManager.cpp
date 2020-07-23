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

	plEnCollision();
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

void enemyManager::setStage1()
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

void enemyManager::setStage2()
{

}

//==================================플레이어가 맞을 때==================================//
void enemyManager::plEnCollision()
{
	RECT temp;

	//==================================남자애==================================//
	for (int i = 0; i < _vBoy.size(); ++i)
	{
		if (IntersectRect(&temp, &_player->getPlayerRect(), &_vBoy[i]->getAtk()) &&
			(_player->getShadowY() - _vBoy[i]->getZ() < 10 && _vBoy[i]->getZ() - _player->getShadowY() < 10))
		{
			_player->playerDamage(2); 
			_vBoy[i]->setAtk(0, 0, 0, 0);
			_vBoy[i]->setStrike(true);

			if (!_player->getDirectionX())
			{
				_player->setAni(KEYANIMANAGER->findAnimation("P_LEFT_HIT"), IMAGEMANAGER->findImage("PLAYER_HIT"));
				_player->setState(_player->getHitState());
			}

			if (_player->getDirectionX())
			{
				_player->setAni(KEYANIMANAGER->findAnimation("P_RIGHT_HIT"), IMAGEMANAGER->findImage("PLAYER_HIT"));
				_player->setState(_player->getHitState());
			}
		}
	}

	//==================================여자애==================================//
	for (int i = 0; i < _vGirl.size(); ++i)
	{
		if (IntersectRect(&temp, &_player->getPlayerRect(), &_vGirl[i]->getAtk()) &&
			(_player->getShadowY() - _vGirl[i]->getZ() < 10 && _vGirl[i]->getZ() - _player->getShadowY() < 10))
		{
			_player->playerDamage(2);
			_vGirl[i]->setAtk(0, 0, 0, 0);
			_vGirl[i]->setStrike(true);

			if (!_player->getDirectionX())
			{
				_player->setAni(KEYANIMANAGER->findAnimation("P_LEFT_HIT"), IMAGEMANAGER->findImage("PLAYER_HIT"));
				_player->setState(_player->getHitState());
			}

			if (_player->getDirectionX())
			{
				_player->setAni(KEYANIMANAGER->findAnimation("P_RIGHT_HIT"), IMAGEMANAGER->findImage("PLAYER_HIT"));
				_player->setState(_player->getHitState());
			}
		}
	}
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

