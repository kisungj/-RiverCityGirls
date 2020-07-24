#include "stdafx.h"
#include "enemy.h"

enemy::enemy()
{
}

enemy::~enemy()
{
}

HRESULT enemy::init(float x, float y, ENEMYTYPE et)
{
	{
		_idle	 = new enemyIdleState();
		_move	 = new enemyMoveState();
		_run	 = new enemyRunState();
		_jump	 = new enemyJumpState();
		_attack	 = new enemyAttackState();
		_hit	 = new enemyHitState();
		_down	 = new enemyDownState();
		_dizzy	 = new enemyDizzyState();
		_dead	 = new enemyDeadState();
	}

	addImage();

	_et = et;
	_x = x;
	_y = y;
	_z = y + 100;
	_width = 130;
	_height = 200;

	_rc = RectMakeCenter(_x, _y, _width, _height);
	_shadow = RectMakeCenter(_x, _z, 50, 30);

	switch (_et)
	{
	case ENEMYTYPE::BOY:
		_image = IMAGEMANAGER->findImage("boy_idle");
		break;
	case ENEMYTYPE::GIRL:
		_image = IMAGEMANAGER->findImage("girl_idle");
		break;
	case ENEMYTYPE::CHEER:
		break;
	}
	_shadowImg = IMAGEMANAGER->findImage("enemy_shadow");

	_right = _isHit = false;
	_jumpPower = _gravity = 0;
	_state = _idle;
	_maxHP = 100;
	
	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	/*if (_isJump)
	{
		_jumpPower = 7.f;
		_gravity = 0.2f;
	}

	if (!_isJump)
	{
		_jumpPower = 0;
		_gravity = 0;
	}*/

	_rc = RectMakeCenter(_x, _y, _width, _height);
	_shadow = RectMakeCenter(_x, _y + 100, 80, 30);

	_state->update(*this, _playerRC, _playerX, _playerY, _et);

	if (_isLay) _layCount++;

	pixelCollision();

	//CAMERAMANAGER->setX(_x);
	//CAMERAMANAGER->setY(_y);

	draw();
}

void enemy::render()
{
	CAMERAMANAGER->renderRectangle(getMemDC(), _attackRC);
	//CAMERAMANAGER->renderRectangle(getMemDC(), _rc);
	//CAMERAMANAGER->render(getMemDC(), _shadowImg, _x, _z);
	CAMERAMANAGER->renderRectangle(getMemDC(), _shadow);
	//CAMERAMANAGER->frameRender(getMemDC(), _image, _x , _y , _currentX, _currentY);

	/*char str[256];
	sprintf_s(str, "%d", _maxHP);
	TextOut(getMemDC(), _x, _y - 50, str, strlen(str));*/

	ZORDERMANAGER->addAlphaRender(getMemDC(), renderType::ALPHA_RENDER, _shadowImg, _x, _z, _z - 1, 200);
	ZORDERMANAGER->addFrameRender(getMemDC(), renderType::FRAME_RENDER, _image, _x, _y, _z, _currentX, _currentY);
}

void enemy::directionCheck(RECT rc, float x, float y)
{
	_playerRC = rc;
	_playerX = x;
	_playerY = y;

	//방향 체크
	if (x > _x && _currentX >= _image->getMaxFrameX())
	{
		_right = true;
	}

	if (x < _x && _currentX <= 0)
	{
		_right = false;
	}

	//거리 체크
	if (getDistance(x, y, _x, _z) < 200 && _condition != CONDITION::GREEN && _maxHP > 0) _condition = CONDITION::CLOSE;
	if (getDistance(x, y, _x, _z) > 200 && _condition != CONDITION::GREEN && _maxHP > 0) _condition = CONDITION::SEARCH;
}

void enemy::draw()
{
	_frameCount++;

	if (!_isStop)
	{
		if (_frameCount % 7 == 0)
		{
			if (_right)
			{
				_currentY = 0;
				_currentX++;
				if (_currentX >= _image->getMaxFrameX()) _currentX = 0;
				_image->setFrameX(_currentX);
			}

			if (!_right)
			{
				_currentY = 1;
				_currentX--;
				if (_currentX <= 0) _currentX = _image->getMaxFrameX();
				_image->setFrameX(_currentX);
			}
			_frameCount = 0;
		}
	}
}

void enemy::pixelCollision()
{	
	int _probeU = _shadow.top;
	int _probeB = _shadow.bottom;
	int _probeL = _shadow.left;
	int _probeR = _shadow.right;
	//int _probeV = _shadow.bottom;
	//int _probeH = (_shadow.left + _shadow.right) / 2;
	//_playerX = _shadowX;
	//_playerProbe = _player.bottom;

	//위
	for (int i = _probeU - 5; i < _probeU + 5; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("background")->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);


		if (r == 255 && g == 0 && b == 0)
		{
			_pixel = PIXEL::TOP;
		}

		if (r == 160 && g == 255 && b == 0)
		{
			_condition = CONDITION::GREEN;
			_pixel = PIXEL::TOP;
		}

		if (r == 255 && g == 255 && b == 0)
		{

		}

	}

	//아래
	for (int i = _probeB - 5; i < _probeB + 5; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("background")->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{
			_pixel = PIXEL::BOTTOM;
		}

		if (r == 160 && g == 255 && b == 0)
		{
			_condition = CONDITION::GREEN;
			_pixel = PIXEL::BOTTOM;
		}

		if (r == 255 && g == 255 && b == 0)
		{

		}
	}

	//왼쪽
	for (int i = _probeL - 5; i < _probeL + 5; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("background")->getMemDC(), i, _z);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{
			_pixel = PIXEL::LEFT;
		}

		if (r == 160 && g == 255 && b == 0)
		{
			_condition = CONDITION::GREEN;
			_pixel = PIXEL::LEFT;
		}

		if (r == 255 && g == 0 && b == 255)
		{
			_pixel = PIXEL::TEMP;
		}

		if (r == 255 && g == 255 && b == 0)
		{

		}
	}

	//오른쪽
	for (int i = _probeR - 5; i < _probeR + 5; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("background")->getMemDC(), i, _z);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{
			_pixel = PIXEL::RIGHT;
		}

		if (r == 160 && g == 255 && b == 0)
		{
			_condition = CONDITION::GREEN;
			_pixel = PIXEL::RIGHT;
		}

		if (r == 255 && g == 255 && b == 0)
		{

		}
	}

	//if (!_isJumping)
	//{
	//	_playerY = _shadowY - 110;
	//}
	////cout << _isJumping << endl;

	//if (_isJumping)
	//{
	//	for (int i = _playerProbe - 10; i < _playerProbe + 10; ++i)
	//	{
	//		COLORREF color = GetPixel(IMAGEMANAGER->findImage(_mapStr)->getMemDC(), _playerX, i);

	//		int r = GetRValue(color);
	//		int g = GetGValue(color);
	//		int b = GetBValue(color);

	//		if (r == 255 && g == 255 && b == 0)
	//		{
	//			_isDesk = true;
	//		}
	//		else
	//		{
	//			_isDesk = false;
	//		}
	//	}
	//}
}

void enemy::addImage()
{
	IMAGEMANAGER->addFrameImage("girl_idle", "image/enemy/girl_idle.bmp", 1170, 354, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("girl_walk", "image/enemy/girl_walk.bmp", 1296, 372, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("girl_run", "image/enemy/girl_run.bmp", 1470, 330, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("girl_jump", "image/enemy/girl_jump.bmp", 333, 366, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("girl_attack1", "image/enemy/girl_attack1.bmp", 1239, 354, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("girl_attack2", "image/enemy/girl_attack2.bmp", 1197, 357, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("girl_attack3", "image/enemy/girl_attack3.bmp", 2412, 414, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("girl_hit1", "image/enemy/girl_hit1.bmp", 477, 360, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("girl_hit2", "image/enemy/girl_hit2.bmp", 477, 360, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("girl_hit3", "image/enemy/girl_hit3.bmp", 477, 360, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("girl_groundhit", "image/enemy/girl_groundhit.bmp", 900, 360, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("girl_knockdown", "image/enemy/girl_knockdown.bmp", 7425, 360, 33, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("girl_dizzy", "image/enemy/girl_dizzy.bmp", 456, 324, 4, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("cheer_idle", "image/enemy/cheer_idle.bmp", 1980, 432, 12, 2, true, RGB(255, 0, 255));

	/*
	_idle
	_walk
	_run
	_attack1
	_attack2
	_attack3
	_sidekick
	_hit1
	_hit2
	_hit3
	_groundhit
	_knockdown
	_dizzy
	*/
}
