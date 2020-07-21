#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{

	//방향키로 움직
	//Z키로 점프
	//A키로 기본공격 3단
	//S키로 아이들,워크-> 밟기 // 런->슬라이딩
	//D키로 회오리킥
	//X키로 방어

	IMAGEMANAGER->addFrameImage("PLAYER_IDLE", "image/player/Kyoko_Idle.bmp", 1440, 450, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_WALK", "image/player/Kyoko_Walk.bmp", 1476, 402, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_RUN", "image/player/Kyoko_Run.bmp", 2736, 384, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_JUMP", "image/player/Kyoko_Jump.bmp", 405, 414, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_ATTACK1", "image/player/Kyoko_ComboAttack1.bmp", 1548, 390, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_ATTACK2", "image/player/Kyoko_ComboAttack2.bmp", 1869, 402, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_ATTACK3", "image/player/Kyoko_ComboAttack3.bmp", 2970, 462, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_DIVE", "image/player/Kyoko_Dive.bmp", 5040, 360, 21, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_START", "image/player/Kyoko_BattleStart.bmp", 2964, 420, 26, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_DOWN", "image/player/Kyoko_Down.bmp", 4896, 366, 24, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_OVER", "image/player/Kyoko_GameOver.bmp", 6240, 282, 26, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_GUARD", "image/player/Kyoko_Guard.bmp", 351, 378, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_HIT", "image/player/Kyoko_Hit.bmp", 246, 348, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_STAND_UP", "image/player/Kyoko_StandUp.bmp", 3315, 330, 17, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_STOMP", "image/player/Kyoko_Stomp.bmp", 1290, 420, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_STUNNED", "image/player/Kyoko_Stunned.bmp", 384, 384, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_KICK", "image/player/Kyoko_HurricaneKick.bmp", 2997, 657, 9, 3, true, RGB(255, 0, 255));


	_idle = new idleState();
	_walk = new walkState();
	_run = new runState();
	_jump = new jumpState();
	_attack = new attackState();
	_hit = new hitState();
	_invin = new invinState();
	_start = new startState();
	_guard = new guardState();

	_state = _start;
	_img = IMAGEMANAGER->findImage("PLAYER_START");

	_shadowX = WINSIZEX / 2 - 120;
	_shadowY = WINSIZEY / 2 + 350;
	_playerX = _shadowX;
	_playerY = _shadowY - 110;
	_runCount = 0;
	
	_directionX = true;

	_isAttack = _attacked = false;

	keyAnimation();

	_attackX = _attackY = _attackSizeX = _attackSizeY = 10;

	_jumpPower = _gravity = 0;
	_shadow = RectMakeCenter(_shadowX, _playerY, 80, 30);
	_player = RectMakeCenter(_playerX, _playerY, 110, 200);
	_attackRc = RectMakeCenter(_attackX, _attackY, _attackSizeX, _attackSizeY);
	_playerMotion = KEYANIMANAGER->findAnimation("P_RIGHT_START");
	_playerMotion->start();

	_isJumping = false;

	_currentHP = _maxHP = 100;

	_probeV = _shadow.bottom;
	_probeH = _shadowX;
	_playerProbe = _player.bottom;

	_mapStr = "pixel2";

	return S_OK;
}

void player::release()
{
}



void player::update()
{
	KEYANIMANAGER->update();
	_probeV = _shadow.bottom;
	_probeH = (_shadow.left+ _shadow.right)/2;
	_playerX = _shadowX;
	_playerProbe = _player.bottom;

	_state->update(*this);

	//픽셀충돌
	for (int i = _probeV - 40; i < _probeV -35; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(_mapStr)->getMemDC(), (_shadow.right + _shadow.left) / 2, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);


		if ((r == 255 && g == 0 && b == 255)|| (r == 0 && g == 0 && b == 255) || (r == 255 && g == 255 && b == 0))
		{
			_isTop = true;
		}
		else
		{
			_isTop = false;
		}
	}

	for (int i = _probeV + 5; i < _probeV +10; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(_mapStr)->getMemDC(), (_shadow.right + _shadow.left) / 2, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 255) || (r == 0 && g == 0 && b == 255) || (r == 255 && g == 255 && b == 0))
		{
			_isBottom = true;
		}
		else
		{
			_isBottom = false;
		}

	}
	for (int i = _probeH - 40; i < _probeH - 35; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(_mapStr)->getMemDC(),i, (_shadow.top + _shadow.bottom) / 2);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 255) || (r == 0 && g == 0 && b == 255) || (r == 255 && g == 255 && b == 0))
		{
			_isLeft = true;
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
		
		else
		{
			_isRight = false;
		}
	}

	if (!_isJumping)
	{
		_playerY = _shadowY - 110;
	}
	cout << _isJumping << endl;

	if (_isJumping)
	{
		for (int i = _playerProbe -10; i < _playerProbe + 10; ++i)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage(_mapStr)->getMemDC(), i, (_shadow.top + _shadow.bottom) / 2);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 255 && b == 0)
			{
				_isDesk = true;
			}

			else
			{
				_isDesk = false;
			}
		}
	}


	_shadow = RectMakeCenter(_shadowX, _shadowY, 80, 30);
	_player = RectMakeCenter(_playerX, _playerY, 110, 200);
	_attackRc = RectMakeCenter(_attackX, _attackY, _attackSizeX, _attackSizeY);
}

void player::render()
{
	//CAMERAMANAGER->renderRectangle(getMemDC(), _player);
	CAMERAMANAGER->renderRectangle(getMemDC(), _shadow);
	CAMERAMANAGER->renderRectangle(getMemDC(), _attackRc);
	CAMERAMANAGER->aniRender(getMemDC(), _img, _playerX, _playerY, _playerMotion);
	//Rectangle(getMemDC(), _player);
	//Rectangle(getMemDC(), _probeV - 5, 100, _probeV + 5, 110);
	//_img->aniRender(getMemDC(), _player.left, _player.top, _playerMotion);

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
