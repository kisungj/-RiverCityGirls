#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{

	IMAGEMANAGER->addFrameImage("PLAYER_IDLE", "image/player/Kyoko_Idle.bmp", 1440, 450, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_WALK", "image/player/Kyoko_Walk.bmp", 1476, 402, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_RUN", "image/player/Kyoko_Run.bmp", 2736, 384, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_JUMP", "image/player/Kyoko_Jump.bmp", 405, 414, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_RUN", "image/player/Kyoko_Run.bmp", 2736, 384, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_ATTACK1", "image/player/Kyoko_ComboAttack1.bmp", 1548, 390, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_ATTACK2", "image/player/Kyoko_ComboAttack2.bmp", 1869, 402, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_ATTACK3", "image/player/Kyoko_ComboAttack3.bmp", 2970, 462, 9, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("PLAYER_JUMP", "image/player/Kyoko_Jump.bmp", 405, 414, 3, 2, true, RGB(255, 0, 255));



	_idle = new idleState();
	_walk = new walkState();
	_run = new runState();
	_jump = new jumpState();
	_attack = new attackState();
	_hit = new hitState();

	_state = _idle;
	_img = IMAGEMANAGER->findImage("PLAYER_IDLE");

	_shadowX = WINSIZEX / 2;
	_shadowY = WINSIZEY / 2 + 100;
	_playerX = _shadowX;
	_playerY = _shadowY - 110;
	_runCount = 0;
	
	_directionX = true;

	_isAttack = _attacked = false;

	keyAnimation();


	_jumpPower = _gravity = 0;
	_rc = RectMakeCenter(_shadowX, _playerY, 80, 30);
	_player = RectMakeCenter(_playerX, _playerY, _img->getFrameWidth(), _img->getFrameHeight());
	_playerMotion = KEYANIMANAGER->findAnimation("P_RIGHT_IDLE");
	_playerMotion->start();

	_isJumping = false;


	_probeV = _rc.bottom;
	_probeH = _shadowX;

	return S_OK;
}

void player::release()
{
}



void player::update()
{
	KEYANIMANAGER->update();
	_probeV = _rc.bottom;
	_probeH = (_rc.left+ _rc.right)/2;
	_playerX = _shadowX;
	//_playerY = _y - 110;

	_state->update(*this);

	cout << _runCount << endl;
	//ÇÈ¼¿Ãæµ¹
	for (int i = _probeV - 40; i < _probeV -35; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel1")->getMemDC(), (_rc.right + _rc.left) / 2, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 255)
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
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel1")->getMemDC(), (_rc.right + _rc.left) / 2, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 255)
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
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel1")->getMemDC(),i, (_rc.top + _rc.bottom) / 2);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 255)
		{
			_isLeft = true;
		}
		else
		{
			_isLeft = false;
		}
	}
	for (int i = _probeH + 55; i < _probeH + 60; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel1")->getMemDC(), i, (_rc.top + _rc.bottom) / 2);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 255)
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



	_rc = RectMakeCenter(_shadowX, _shadowY, 80, 30);
	_player = RectMakeCenter(_playerX, _playerY, _img->getFrameWidth(), _img->getFrameHeight());


	CAMERAMANAGER->setX(_shadowX);
	CAMERAMANAGER->setY(_shadowY);
	
}

void player::render()
{
	CAMERAMANAGER->renderRectangle(getMemDC(), _player);
	CAMERAMANAGER->renderRectangle(getMemDC(), _rc);
	CAMERAMANAGER->aniRender(getMemDC(), _img, _player.left, _player.top, _playerMotion);
	//Rectangle(getMemDC(), _player);
	//Rectangle(getMemDC(), _rc);
	//_img->aniRender(getMemDC(), _player.left, _player.top, _playerMotion);

}

void player::keyAnimation()
{
	int rightIdle[] = { 12,13,14,15,16,17,18,19,20,21,22,23 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_IDLE", "PLAYER_IDLE", rightIdle, 12, 10, true);
	int leftIdle[] = { 11,10,9,8,7,6,5,4,3,2,1,0 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_IDLE", "PLAYER_IDLE", leftIdle, 12, 10, true);

	int rightWalk[] = { 12,13,14,15,16,17,18,19,20,21,22,23 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_WALK", "PLAYER_WALK", rightWalk, 12, 10, true);
	int leftWalk[] = { 11,10,9,8,7,6,5,4,3,2,1,0 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_WALK", "PLAYER_WALK", leftWalk, 12, 10, true);

	int rightRun[] = { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_RUN", "PLAYER_RUN", rightRun, 16, 15, true);
	int leftRun[] = { 15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_RUN", "PLAYER_RUN", leftRun, 16, 15, true);

	int leftAttack1[] = { 6,7,8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_ATTACK1", "PLAYER_ATTACK1", leftAttack1, 6, 10, false);
	int rightAttack1[] = { 5,4,3,2,1,0 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_ATTACK1", "PLAYER_ATTACK1", rightAttack1, 6, 10, false);

	int leftAttack2[] = { 7,8,9,10,11,12,13 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_ATTACK2", "PLAYER_ATTACK2", leftAttack2, 7, 10, false);
	int rightAttack2[] = { 6,5,4,3,2,1,0 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_ATTACK2", "PLAYER_ATTACK2", rightAttack2, 7, 10, false);

	int leftAttack3[] = { 9,10,11,12,13,14,15,16,17 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_ATTACK3", "PLAYER_ATTACK3", leftAttack3, 9, 10, false);
	int rightAttack3[] = { 8,7,6,5,4,3,2,1,0 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_ATTACK3", "PLAYER_ATTACK3", rightAttack3, 9, 10, false);

	int rightJump[] = { 3, 4 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_JUMP", "PLAYER_JUMP", rightJump, 2, 5, false);
	int leftJump[] = { 2, 1 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_JUMP", "PLAYER_JUMP", leftJump, 2, 5, false);
	int rightFall[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_FALL", "PLAYER_JUMP", rightFall, 1, 10, false);
	int leftFall[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_FALL", "PLAYER_JUMP", leftFall, 1, 10, false);

}
