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

		if (_vBoy[i]->getCondition() == CONDITION::DEAD) eraseBoy(i);
	}

	for (int i = 0; i < _vGirl.size(); i++)
	{
		_vGirl[i]->update();
		_vGirl[i]->directionCheck(_player->getPlayerRect(), _player->getPlayerX(), _player->getShadowY());

		if (_vGirl[i]->getCondition() == CONDITION::DEAD) eraseGirl(i);
	}

	if (!_isCollision)
	{
		boyPlCollision();
		girlPlCollision();
		cheerPlCollision();
	}

	/*if (_isCollision)
	{
		_attackCount++;
		if (_attackCount > 19)
		{
			_attackCount = 0;
			_isCollision = false;
		}
	}*/

	cout << _isCollision << endl;
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

//==================================남자애==================================//
void enemyManager::boyPlCollision()
{
	RECT temp;

	for (int i = 0; i < _vBoy.size(); ++i)
	{
		if (IntersectRect(&temp, &_player->getPlayerRect(), &_vBoy[i]->getAtk()) &&
			(_player->getShadowY() - _vBoy[i]->getZ() < 10 && _vBoy[i]->getZ() - _player->getShadowY() < 10) &&
			_player->getAni() != KEYANIMANAGER->findAnimation("P_RIGHT_DOWN") && _player->getAni() != KEYANIMANAGER->findAnimation("P_LEFT_DOWN") &&
			_player->getAni() != KEYANIMANAGER->findAnimation("P_RIGHT_STAND_UP") && _player->getAni() != KEYANIMANAGER->findAnimation("P_LEFT_STAND_UP") &&
			_player->getAni() != KEYANIMANAGER->findAnimation("P_RIGHT_OVER") && _player->getAni() != KEYANIMANAGER->findAnimation("P_LEFT_OVER"))
		{
			_player->playerDamage(2);
			_vBoy[i]->setAtk(0, 0, 0, 0);
			_vBoy[i]->setStrike(true);

			if (_player->getAni() == KEYANIMANAGER->findAnimation("P_RIGHT_GUARD"))
			{
				if (_vBoy[i]->getRight())
				{
					_player->setAni(KEYANIMANAGER->findAnimation("P_RIGHT_HIT"), IMAGEMANAGER->findImage("PLAYER_HIT"));
					_player->setState(_player->getHitState());
				}
			}

			else if (_player->getAni() == KEYANIMANAGER->findAnimation("P_LEFT_GUARD"))
			{
				if (!_vBoy[i]->getRight())
				{
					_player->setAni(KEYANIMANAGER->findAnimation("P_LEFT_HIT"), IMAGEMANAGER->findImage("PLAYER_HIT"));
					_player->setState(_player->getHitState());
				}
			}

			if (_player->getAni() != KEYANIMANAGER->findAnimation("P_LEFT_GUARD") && _player->getAni() != KEYANIMANAGER->findAnimation("P_RIGHT_GUARD"))
			{
				if (_vBoy[i]->getCondition() == CONDITION::STRONG) _player->setIsDown(true);

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
			_isCollision = true;
		}
	}
}

//==================================여자애==================================//
void enemyManager::girlPlCollision()
{
	RECT temp;

	for (int i = 0; i < _vGirl.size(); ++i)
	{
		if (IntersectRect(&temp, &_player->getPlayerRect(), &_vGirl[i]->getAtk()) &&
			(_player->getShadowY() - _vGirl[i]->getZ() < 10 && _vGirl[i]->getZ() - _player->getShadowY() < 10) &&
			_player->getAni() != KEYANIMANAGER->findAnimation("P_RIGHT_DOWN") && _player->getAni() != KEYANIMANAGER->findAnimation("P_LEFT_DOWN") &&
			_player->getAni() != KEYANIMANAGER->findAnimation("P_RIGHT_STAND_UP") && _player->getAni() != KEYANIMANAGER->findAnimation("P_LEFT_STAND_UP") &&
			_player->getAni() != KEYANIMANAGER->findAnimation("P_RIGHT_OVER") && _player->getAni() != KEYANIMANAGER->findAnimation("P_LEFT_OVER"))
		{
			_player->playerDamage(2);
			_vGirl[i]->setAtk(0, 0, 0, 0);
			_vGirl[i]->setStrike(true);

			if (_player->getAni() == KEYANIMANAGER->findAnimation("P_RIGHT_GUARD"))
			{
				if (_vGirl[i]->getRight())
				{
					_player->setAni(KEYANIMANAGER->findAnimation("P_RIGHT_HIT"), IMAGEMANAGER->findImage("PLAYER_HIT"));
					_player->setState(_player->getHitState());
				}
			}
			else if (_player->getAni() == KEYANIMANAGER->findAnimation("P_LEFT_GUARD"))
			{
				if (!_vGirl[i]->getRight())
				{
					_player->setAni(KEYANIMANAGER->findAnimation("P_LEFT_HIT"), IMAGEMANAGER->findImage("PLAYER_HIT"));
					_player->setState(_player->getHitState());
				}
			}

			if (_player->getAni() != KEYANIMANAGER->findAnimation("P_LEFT_GUARD") && _player->getAni() != KEYANIMANAGER->findAnimation("P_RIGHT_GUARD"))
			{
				if (_vGirl[i]->getCondition() == CONDITION::STRONG) _player->setIsDown(true);

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
			_isCollision = true;
		}
	}
}

void enemyManager::cheerPlCollision()
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

