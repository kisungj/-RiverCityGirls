#include "stdafx.h"
#include "player.h"
#include "boss.h"
#include "enemyManager.h"


HRESULT player::init()
{
	//++++++플레이어 사용법++++++
	//방향키로 움직
	//Z키로 점프
	//A키로 기본공격 3단
	//S키로 아이들,워크-> 밟기 // 런->슬라이딩
	//D키로 회오리킥
	//X키로 방어

	_shadowImg = IMAGEMANAGER->findImage("PLAYER_SHADOW");


	_idle = new idleState();
	_walk = new walkState();
	_run = new runState();
	_jump = new jumpState();
	_attack = new attackState();
	_hit = new hitState();
	_down = new downState();
	_start = new startState();
	_over = new overState();
	_guard = new guardState();
	_stun = new stunState();

	_state = _start;
	_img = IMAGEMANAGER->findImage("PLAYER_START");

	_shadowX = WINSIZEX / 2 - 120;
	_shadowY = WINSIZEY / 2 + 350;
	_playerX = _shadowX;
	_playerY = _shadowY - 110;
	_runCount = 0;
	
	_directionX = true;

	_isAttack = _attacked = false;
	_isDeskFall = false;
	_attackRect = true;

	keyAnimation();

	_attackX = _attackY = _attackSizeX = _attackSizeY = 10;

	_gameOver = false;

	_jumpPower = _gravity = 0;
	_shadow = RectMakeCenter(_shadowX, _shadowY, 80, 30);
	_player = RectMakeCenter(_playerX, _playerY, 110, 200);
	_attackRc = RectMakeCenter(_attackX, _attackY, _attackSizeX, _attackSizeY);
	_playerMotion = KEYANIMANAGER->findAnimation("P_RIGHT_START");
	_playerMotion->start();

	_isJumping = false;

	_shadowAlpha = 200;

	_currentHP = _maxHP = 100;

	_probeV = _shadow.bottom;
	_probeH = _shadowX;
	_playerProbe = _player.bottom;

	_deskTimer = 0;

	_mapStr = "pixel2";
	_enemyBLay = false;
	_enemyGLay = false;
	
	return S_OK;
}

void player::release()
{
}



void player::update()
{

	//cout << _ptMouse.x << endl;
	//cout << _ptMouse.y << endl;
	KEYANIMANAGER->update();
	_probeV = _shadow.bottom;
	_probeH = (_shadow.left+ _shadow.right)/2;
	_playerX = _shadowX;
	_playerProbe = _player.bottom;

	_state->update(*this);
	
	pixelCol();

	enemyCol();
	bossCol();

	boolCheck();
	

	_shadow = RectMakeCenter(_shadowX, _shadowY, 80, 30);
	_player = RectMakeCenter(_playerX, _playerY, 110, 200);
	_attackRc = RectMakeCenter(_attackX, _attackY, _attackSizeX, _attackSizeY);

	ZORDERMANAGER->addAlphaRender(getMemDC(), renderType::ALPHA_RENDER, _shadowImg, _shadowX, _shadowY, _shadowY, _shadowAlpha);
	ZORDERMANAGER->addAniRender(getMemDC(), renderType::ANI_RENDER, _img, _playerX, _playerY, _shadowY, _playerMotion);
}

void player::render()
{
	//CAMERAMANAGER->renderRectangle(getMemDC(), _player);
	//CAMERAMANAGER->renderRectangle(getMemDC(), _shadow);
	if (_attackRect)
	{
		CAMERAMANAGER->renderRectangle(getMemDC(), _attackRc);
	}
	/*CAMERAMANAGER->alphaRender(getMemDC(), _shadowImg, _shadowX, _shadowY, _shadowAlpha);
	CAMERAMANAGER->aniRender(getMemDC(), _img, _playerX, _playerY, _playerMotion);*/
	//Rectangle(getMemDC(), _player);
	//Rectangle(getMemDC(), _probeV - 5, 100, _probeV + 5, 110);
	//_img->aniRender(getMemDC(), _player.left, _player.top, _playerMotion);
	//IMAGEMANAGER->findImage("PLAYER_STRONG")->render(getMemDC());

}

void player::keyAnimation()
{
	int rightIdle[] = { 12,13,14,15,16,17,18,19,20,21,22,23 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_IDLE", "PLAYER_IDLE", rightIdle, 12, 13, true);
	int leftIdle[] = { 11,10,9,8,7,6,5,4,3,2,1,0 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_IDLE", "PLAYER_IDLE", leftIdle, 12, 13, true);

	int rightWalk[] = { 12,13,14,15,16,17,18,19,20,21,22,23 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_WALK", "PLAYER_WALK", rightWalk, 12, 13, true);
	int leftWalk[] = { 11,10,9,8,7,6,5,4,3,2,1,0 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_WALK", "PLAYER_WALK", leftWalk, 12, 13, true);

	int rightRun[] = { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_RUN", "PLAYER_RUN", rightRun, 16, 20, true);
	int leftRun[] = { 15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_RUN", "PLAYER_RUN", leftRun, 16, 20, true);

	int rightAttack1[] = { 6,7,8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_ATTACK1", "PLAYER_ATTACK1", rightAttack1, 6, 13, false);
	int lefttAttack1[] = { 5,4,3,2,1,0 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_ATTACK1", "PLAYER_ATTACK1", lefttAttack1, 6, 13, false);

	int rightAttack2[] = { 7,8,9,10,11,12,13 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_ATTACK2", "PLAYER_ATTACK2", rightAttack2, 7, 13, false);
	int leftAttack2[] = { 6,5,4,3,2,1,0 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_ATTACK2", "PLAYER_ATTACK2", leftAttack2, 7, 13, false);

	int rightAttack3[] = { 9,10,11,12,13,14,15,16,17 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_ATTACK3", "PLAYER_ATTACK3", rightAttack3, 9, 13, false);
	int leftAttack3[] = { 8,7,6,5,4,3,2,1,0 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_ATTACK3", "PLAYER_ATTACK3", leftAttack3, 9, 13, false);

	int rightDive[] = { 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_DIVE", "PLAYER_DIVE", rightDive, 21, 13, false);
	int leftDive[] = { 20, 19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_DIVE", "PLAYER_DIVE", leftDive, 21, 13, false);
	
	int rightStart[] = { 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46
	, 47, 48, 49, 50, 51 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_START", "PLAYER_START", rightStart, 26, 8, false);
	
	int rightDown[] = { 24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_DOWN", "PLAYER_DOWN", rightDown, 24, 13, false);
	int leftDown[] = { 23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_DOWN", "PLAYER_DOWN", leftDown, 24, 13, false);
	
	int rightOver[] = { 26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_OVER", "PLAYER_OVER", rightOver, 26, 13, false);
	int leftOver[] = { 25, 24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_OVER", "PLAYER_OVER", leftOver, 26, 13, false);
	
	int rightGuard[] = { 3,4,5 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_GUARD", "PLAYER_GUARD", rightGuard, 3, 13, false);
	int leftGuard[] = { 2,1,0 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_GUARD", "PLAYER_GUARD", leftGuard, 3, 13, false);
	
	int rightHit[] = { 2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_HIT", "PLAYER_HIT", rightHit, 2, 8, true);
	int leftHit[]{ 1, 0 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_HIT", "PLAYER_HIT", leftHit, 2, 8, true);
	
	int rightStandUp[] = { 17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_STAND_UP", "PLAYER_STAND_UP", rightStandUp, 17, 13, false);
	int leftStandUp[] = { 16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_STAND_UP", "PLAYER_STAND_UP", leftStandUp, 17, 13, false);
	
	int rightStomp[] = { 10,11,12,13,14,15,16,17,18,19 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_STOMP", "PLAYER_STOMP", rightStomp, 10, 13, false);
	int leftStomp[] = { 9,8,7,6,5,4,3,2,1,0 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_STOMP", "PLAYER_STOMP", leftStomp, 10, 13, false);
	
	int rightStunned[] = { 4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_STUNNED", "PLAYER_STUNNED", rightStunned, 4, 13, true);
	int leftStunned[] = { 3,2,1,0 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_STUNNED", "PLAYER_STUNNED", leftStunned, 4, 13, true);
	
	
	int rightKick[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_KICK", "PLAYER_KICK", rightKick, 24, 13, false);

	
	int rightStrong[] = { 19,18,17,16,15,14,13,12,11,10 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_STRONG_ATTACK", "PLAYER_STRONG", rightStrong, 10, 13, false);
	int leftStrong[] = { 0,1,2,3,4,5,6,7,8,9 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_STRONG_ATTACK", "PLAYER_STRONG", leftStrong, 10, 13, false);

	
	int rightJump[] = { 3, 4 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_JUMP", "PLAYER_JUMP", rightJump, 2, 10, false);
	int leftJump[] = { 2, 1 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_JUMP", "PLAYER_JUMP", leftJump, 2, 10, false);
	int rightFall[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_FALL", "PLAYER_JUMP", rightFall, 1, 13, false);
	int leftFall[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_FALL", "PLAYER_JUMP", leftFall, 1, 13, false);

}

void player::playerDamage(float damage)
{
	_currentHP -= damage;
}

void player::mouseCol()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{

		if (PtInRect(&_player, _ptMouse))
		{
			//cout << "dd" << endl;

			if (!_directionX)
			{
				setAni(KEYANIMANAGER->findAnimation("P_LEFT_HIT"), IMAGEMANAGER->findImage("PLAYER_HIT"));
				setState(getHitState());
				playerDamage(10);
			}
			if (_directionX)
			{
				setAni(KEYANIMANAGER->findAnimation("P_RIGHT_HIT"), IMAGEMANAGER->findImage("PLAYER_HIT"));
				setState(getHitState());
				playerDamage(10);
			}
		}

	}
}

void player::pixelCol()
{
	if (!_isDesk)
	{

		//맵 충돌 하고 올라와있음 하지마
		for (int i = _probeV - 40; i < _probeV - 35; ++i)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage(_mapStr)->getMemDC(), (_shadow.right + _shadow.left) / 2, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);


			if ((r == 255 && g == 0 && b == 255) || (r == 0 && g == 0 && b == 255) || (r == 255 && g == 255 && b == 0))
			{

				_isTop = true;
			}
			else if (_isJumping)
			{
				if (r == 160 && g == 255 && b == 0)
				{
					_isTop = true;
					break;
				}
				else
				{
					_isTop = false;
					break;
				}
			}
			else
			{
				_isTop = false;
			}
		}

		for (int i = _probeV + 5; i < _probeV + 10; ++i)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage(_mapStr)->getMemDC(), (_shadow.right + _shadow.left) / 2, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 255) || (r == 0 && g == 0 && b == 255) || (r == 255 && g == 255 && b == 0))
			{
				_isBottom = true;
			}
			else if (_isJumping)
			{
				if (r == 160 && g == 255 && b == 0)
				{
					_isBottom = true;
					break;
				}
				else
				{
					_isBottom = false;
					break;
				}
			}

			else
			{
				_isBottom = false;
			}
		}
		for (int i = _probeH - 40; i < _probeH - 35; ++i)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage(_mapStr)->getMemDC(), i, (_shadow.top + _shadow.bottom) / 2);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 255) || (r == 0 && g == 0 && b == 255) || (r == 255 && g == 255 && b == 0))
			{
				_isLeft = true;
			}
			else if (_isJumping)
			{
				if (r == 160 && g == 255 && b == 0)
				{
					_isLeft = true;
					break;
				}
				else
				{
					_isLeft = false;
					break;
				}
			}
			else
			{
				_isLeft = false;
			}
		}
		for (int i = _probeH + 45; i < _probeH + 50; ++i)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage(_mapStr)->getMemDC(), i, (_shadow.top + _shadow.bottom) / 2);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 255) || (r == 0 && g == 0 && b == 255) || (r == 255 && g == 255 && b == 0))
			{
				_isRight = true;
			}
			else if (_isJumping)
			{
				if (r == 160 && g == 255 && b == 0)
				{
					_isRight = true;
					break;
				}
				else
				{
					_isRight = false;
					break;
				}
			}
			else
			{
				_isRight = false;
			}

		}


		//cout << _runCount << endl;
		//점프중에
		if (_isJumping)
		{
			_runCount = 0;
			for (int i = _probeV + 5; i < _probeV + 10; ++i)
			{
				COLORREF color = GetPixel(IMAGEMANAGER->findImage(_mapStr)->getMemDC(), _playerX, i);

					int r = GetRValue(color);
					int g = GetGValue(color);
					int b = GetBValue(color);
					if (!(r == 255 && g == 0 && b == 0))
					{
						_isRight = true;
						if ((r == 160 && g == 255 && b == 0) && _jumpPower < 0 && !_isDeskFall)
						{
						_isLeft = true;
						_isTop = true;
						_isBottom = true;
						_isDesk = true;
						_shadowY -= 110;
						}
						break;
					}
			}
		}
	}
	//cout << _isDesk << endl;
	if (_isDesk)
	{
		_deskTimer++;
		_shadowAlpha = 200;
		if (_deskTimer > 20)
		{
			_deskTimer = 0;
			if(KEYMANAGER->isOnceKeyDown('Z'))
			{
				if (!_directionX)
				{
					setAni(KEYANIMANAGER->findAnimation("P_LEFT_JUMP"), IMAGEMANAGER->findImage("PLAYER_JUMP"));
						setState(getHitState());
						playerDamage(10);
				}
				if (_directionX)
				{
					setAni(KEYANIMANAGER->findAnimation("P_RIGHT_JUMP"), IMAGEMANAGER->findImage("PLAYER_JUMP"));
						setState(getHitState());
					playerDamage(10);
				}
			}

			for (int i = _probeV - 20; i < _probeV - 15; ++i)
			{
				COLORREF color = GetPixel(IMAGEMANAGER->findImage(_mapStr)->getMemDC(), _playerX, i);

				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				if (!(r == 255 && g == 255 && b == 0))
				{
					//cout << "d" << endl;

					_gravity = 0.5f;
					_jumpPower = 0;
					_isDesk = false;
					_isJumping = true;

					_isDeskFall = true;
					_shadowY += 110;
					_runCount = 0;
					if (!_directionX)
					{
						setState(getJumpState());
					}
					if (_directionX)
					{
						setState(getJumpState());
					}
					break;
				}
				else
				{
				//	cout << "d" << endl;

				}
			}
		}
	}
}

void player::boolCheck()
{
	//점프중이 아니고 데스크랑 닿아있는 것도 아니고
	//얘는 기본
	if (!_isJumping)
	{
		_playerY = _shadowY - 110;
		_isDeskFall = false;
	}
	RECT temp;
	for (int i = 0; i < _enemy->getVBoy().size(); ++i)
	{
		if (_enemy->getVBoy()[i]->getLay())
		{
			if (IntersectRect(&temp, &_player, &_enemy->getVBoy()[i]->getRC()))
			{
				_enemyBLay = true;
				break;
			}
		}
		if (!_enemy->getVBoy()[i]->getLay())
		{
			_enemyBLay = false;
		}
	}
	for (int i = 0; i < _enemy->getVGirl().size(); ++i)
	{
		if (_enemy->getVGirl()[i]->getLay())
		{
			if (IntersectRect(&temp, &_player, &_enemy->getVGirl()[i]->getRC()))
			{
				_enemyGLay = true;
				break;
			}
		}
		if (!_enemy->getVGirl()[i]->getLay())
		{
			_enemyGLay = false;
		}
	}
	
}

void player::enemyCol()
{
	RECT temp;
	if (_state == _attack || KEYANIMANAGER->findAnimation("P_RIGHT_STRONG_ATTACK")->isPlay() || KEYANIMANAGER->findAnimation("P_LEFT_STRONG_ATTACK")->isPlay())
	{
		for (int i = 0; i < _enemy->getVBoy().size(); ++i)
		{
			if (_enemy->getVBoy()[i]->getLay())
			{
				if (IntersectRect(&temp, &_attackRc, &_enemy->getVBoy()[i]->getRC()))
				{
					if (KEYANIMANAGER->findAnimation("P_RIGHT_DIVE")->isPlay() || KEYANIMANAGER->findAnimation("P_LEFT_DIVE")->isPlay())
					{
						//_attackX = _attackY = _attackSizeX = _attackSizeY = 0;
						_enemy->getVBoy()[i]->setHP(10);
					}
				}

			}
			else if (_shadowY + 15 > _enemy->getVBoy()[i]->getZ() && _shadowY - 15 < _enemy->getVBoy()[i]->getZ() && !_enemy->getVBoy()[i]->getLay())
			{
				if (_attackRect)
				{
					if (IntersectRect(&temp, &_attackRc, &_enemy->getVBoy()[i]->getRC()))
					{

						EFFECTMANAGER->play("e_hit_effect", (temp.left + temp.right) * 0.5f, (temp.top + temp.bottom) * 0.5f);
						//_attackX = _attackY = _attackSizeX = _attackSizeY = 0;
						_enemy->getVBoy()[i]->setOuch(true);
						_enemy->getVBoy()[i]->setHitCount(1);
						_enemy->getVBoy()[i]->setHP(10);
						_attackRect = false;
					}
				}
			}

		}

		for (int i = 0; i < _enemy->getVGirl().size(); ++i)
		{
			if (_shadowY + 15 > _enemy->getVGirl()[i]->getZ() && _shadowY - 15 < _enemy->getVGirl()[i]->getZ())
			{
				if (_enemy->getVGirl()[i]->getLay())
				{
					if (KEYANIMANAGER->findAnimation("P_RIGHT_DIVE")->isPlay() || KEYANIMANAGER->findAnimation("P_LEFT_DIVE")->isPlay())
					{
						_attackX = _attackY = _attackSizeX = _attackSizeY = 0;
						_enemy->getVGirl()[i]->setHP(10);
					}

				}

				else if (_shadowY + 15 > _enemy->getVGirl()[i]->getZ() && _shadowY - 15 < _enemy->getVGirl()[i]->getZ() && !_enemy->getVGirl()[i]->getLay())
				{
					if (IntersectRect(&temp, &_attackRc, &_enemy->getVGirl()[i]->getRC()))
					{
						_attackX = _attackY = _attackSizeX = _attackSizeY = 0;
						_enemy->getVGirl()[i]->setOuch(true);
						_enemy->getVGirl()[i]->setHitCount(1);
						_enemy->getVGirl()[i]->setHP(10);
						_attackRect = false;
					}
				}
			}

		}
	}

}

void player::bossCol()
{
	RECT temp;
	if (_state == _attack || KEYANIMANAGER->findAnimation("P_RIGHT_STRONG_ATTACK")->isPlay() || KEYANIMANAGER->findAnimation("P_RIGHT_STRONG_ATTACK")->isPlay())
	{
		/*if (_shadowY + 15 > _boss->getPointerRect() && _shadowY - 15 < _enemy->getVBoy()[i]->getZ())
		{*/
		if (_attackRect)
		{
			if (IntersectRect(&temp, &_attackRc, _boss->getPointerRect()))
			{

				EFFECTMANAGER->play("e_hit_effect", (temp.left + temp.right) * 0.5f, (temp.top + temp.bottom) * 0.5f);
				_attackX = _attackY = _attackSizeX = _attackSizeY = 0;
				_boss->hit(_playerX, _shadowY, 10);
				_attackRect = false;

			}

		}
	}
}

