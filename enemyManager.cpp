#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"

HRESULT enemyManager::init()
{
	_waveCount = 0;
	_wave = WAVE::FIRST;

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

	for (int i = 0; i < _vCheer.size(); i++)
	{
		_vCheer[i]->render();
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

	for (int i = 0; i < _vCheer.size(); i++)
	{
		_vCheer[i]->update();
		_vCheer[i]->directionCheck(_player->getPlayerRect(), _player->getPlayerX(), _player->getShadowY());
	}

	boyPlCollision();
	girlPlCollision();
	cheerPlCollision();
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

	for (int i = 0; i < _vCheer.size(); i++)
	{
		SAFE_DELETE(_vCheer[i]);
	}

	_vBoy.clear();
	_vGirl.clear();
	_vCheer.clear();
}

void enemyManager::setStage1()
{
	for (int i = 0; i < 1; ++i)
	{
		enemy* boy;
		boy = new enemyBoy;
		boy->init(300, WINSIZEY / 2 + 300, ENEMYTYPE::BOY, "background");
	
		_vBoy.push_back(boy);
	}
	
	for (int i = 0; i < 2; ++i)
	{
		enemy* girl;
		girl = new enemyGirl;
		girl->init(1800 + i * 200, (WINSIZEY / 2 + 200) + i * 300, ENEMYTYPE::GIRL, "background");
	
		_vGirl.push_back(girl);
	}
	
}

void enemyManager::setStage2()
{
	switch (_wave)
	{
	case WAVE::FIRST:

		for (int i = 0; i < 2; ++i)
		{
			enemy* boy;
			boy = new enemyBoy;
			boy->init(1500 + i * 1000, WINSIZEY / 2 + 500, ENEMYTYPE::BOY, "stage2pixel");

			_vBoy.push_back(boy);
		}

		for (int i = 0; i < 2; ++i)
		{
			enemy* girl;
			girl = new enemyGirl;
			girl->init(1700 + i * 500, WINSIZEY / 2 + 800, ENEMYTYPE::GIRL, "stage2pixel");

			_vGirl.push_back(girl);
		}
		break;
	}	
}

void enemyManager::waveStage1()
{
	_waveCount++;

	if (_waveCount >= 1200)
	{
		if (_waveCount == 1200)
		{
			_rnd = RND->getInt(2);
		}

		if (_rnd == 0)
		{
			for (int i = 0; i < 1; ++i)
			{
				enemy* boy;
				boy = new enemyBoy;
				boy->init(1700, 530, ENEMYTYPE::BOY, "background");

				_vBoy.push_back(boy);
			}
		}

		if (_rnd == 1)
		{
			for (int i = 0; i < 1; ++i)
			{
				enemy* girl;
				girl = new enemyGirl;
				girl->init(1700, 530, ENEMYTYPE::GIRL, "background");

				_vGirl.push_back(girl);
			}
		}
		_waveCount = 0;
	}
}

void enemyManager::waveStage2()
{
	switch (_wave)
	{
	case WAVE::FIRST:
		if (_vBoy.size() <= 0 && _vGirl.size() <= 0) _wave = WAVE::SECOND;
		break;
	case WAVE::SECOND:
		break;
	case WAVE::REPEAT:
		break;
	default:
		break;
	}

	switch (_wave)
	{
	case WAVE::FIRST:
		break;
	case WAVE::SECOND:
		/*for (int i = 0; i < 1; ++i)
		{
			enemy* cheer;
			cheer = new enemyGirl;
			cheer->init(1700, WINSIZEY / 2 + 800, ENEMYTYPE::CHEER, "stage2pixel");

			_vCheer.push_back(cheer);
		}*/
		break;

	case WAVE::REPEAT:

		break;
	}

	cout << _vBoy.size() << ", " << _vGirl.size() << endl;
}

//==================================남자애==================================//
void enemyManager::boyPlCollision()
{
	RECT temp;

	for (int i = 0; i < _vBoy.size(); ++i)
	{
		if (IntersectRect(&temp, &_player->getPlayerRect(), &_vBoy[i]->getAtk()) &&
			(_player->getShadowY() - _vBoy[i]->getZ() < 15 && _vBoy[i]->getZ() - _player->getShadowY() < 15) &&
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
				if (_vBoy[i]->getImage() == IMAGEMANAGER->findImage("boy_attack3") || _vBoy[i]->getImage() == IMAGEMANAGER->findImage("boy_sidekick"))
				{
					if (!_player->getDirectionX())
					{
						_player->setAni(KEYANIMANAGER->findAnimation("P_LEFT_DOWN"), IMAGEMANAGER->findImage("PLAYER_DOWN"));
						_player->setState(_player->getDownState());
						_player->setIsDown(true);
					}

					if (_player->getDirectionX())
					{
						_player->setAni(KEYANIMANAGER->findAnimation("P_RIGHT_DOWN"), IMAGEMANAGER->findImage("PLAYER_DOWN"));
						_player->setState(_player->getDownState());
						_player->setIsDown(true);
					}
				}

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
}

//==================================여자애==================================//
void enemyManager::girlPlCollision()
{
	RECT temp;

	for (int i = 0; i < _vGirl.size(); ++i)
	{
		if (IntersectRect(&temp, &_player->getPlayerRect(), &_vGirl[i]->getAtk()) &&
			(_player->getShadowY() - _vGirl[i]->getZ() < 15 && _vGirl[i]->getZ() - _player->getShadowY() < 15) &&
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
				if (_vGirl[i]->getImage() == IMAGEMANAGER->findImage("girl_attack3"))
				{
					if (!_player->getDirectionX())
					{
						_player->setAni(KEYANIMANAGER->findAnimation("P_LEFT_DOWN"), IMAGEMANAGER->findImage("PLAYER_DOWN"));
						_player->setState(_player->getDownState());
						_player->setIsDown(true);
					}

					if (_player->getDirectionX())
					{
						_player->setAni(KEYANIMANAGER->findAnimation("P_RIGHT_DOWN"), IMAGEMANAGER->findImage("PLAYER_DOWN"));
						_player->setState(_player->getDownState());
						_player->setIsDown(true);
					}
				}

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
}

void enemyManager::cheerPlCollision()
{
	RECT temp;

	for (int i = 0; i < _vCheer.size(); ++i)
	{
		if (IntersectRect(&temp, &_player->getPlayerRect(), &_vCheer[i]->getAtk()) &&
			(_player->getShadowY() - _vCheer[i]->getZ() < 15 && _vCheer[i]->getZ() - _player->getShadowY() < 15) &&
			_player->getAni() != KEYANIMANAGER->findAnimation("P_RIGHT_DOWN") && _player->getAni() != KEYANIMANAGER->findAnimation("P_LEFT_DOWN") &&
			_player->getAni() != KEYANIMANAGER->findAnimation("P_RIGHT_STAND_UP") && _player->getAni() != KEYANIMANAGER->findAnimation("P_LEFT_STAND_UP") &&
			_player->getAni() != KEYANIMANAGER->findAnimation("P_RIGHT_OVER") && _player->getAni() != KEYANIMANAGER->findAnimation("P_LEFT_OVER"))
		{
			_player->playerDamage(2);
			_vCheer[i]->setAtk(0, 0, 0, 0);
			_vCheer[i]->setStrike(true);

			if (_player->getAni() == KEYANIMANAGER->findAnimation("P_RIGHT_GUARD"))
			{
				if (_vCheer[i]->getRight())
				{
					_player->setAni(KEYANIMANAGER->findAnimation("P_RIGHT_HIT"), IMAGEMANAGER->findImage("PLAYER_HIT"));
					_player->setState(_player->getHitState());
				}
			}
			else if (_player->getAni() == KEYANIMANAGER->findAnimation("P_LEFT_GUARD"))
			{
				if (!_vCheer[i]->getRight())
				{
					_player->setAni(KEYANIMANAGER->findAnimation("P_LEFT_HIT"), IMAGEMANAGER->findImage("PLAYER_HIT"));
					_player->setState(_player->getHitState());
				}
			}

			if (_player->getAni() != KEYANIMANAGER->findAnimation("P_LEFT_GUARD") && _player->getAni() != KEYANIMANAGER->findAnimation("P_RIGHT_GUARD"))
			{
				if (_vCheer[i]->getImage() == IMAGEMANAGER->findImage("cheer_attack3") || _vCheer[i]->getImage() == IMAGEMANAGER->findImage("cheer_flip"));
				{
					if (!_player->getDirectionX())
					{
						_player->setAni(KEYANIMANAGER->findAnimation("P_LEFT_DOWN"), IMAGEMANAGER->findImage("PLAYER_DOWN"));
						_player->setState(_player->getDownState());
						_player->setIsDown(true);
					}

					if (_player->getDirectionX())
					{
						_player->setAni(KEYANIMANAGER->findAnimation("P_RIGHT_DOWN"), IMAGEMANAGER->findImage("PLAYER_DOWN"));
						_player->setState(_player->getDownState());
						_player->setIsDown(true);
					}
				}

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
	_vCheer.erase(_vCheer.begin() + arrNum);
}

