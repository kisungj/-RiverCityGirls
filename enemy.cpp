#include "stdafx.h"
#include "enemy.h"

enemy::enemy()
{
}

enemy::~enemy()
{
}

HRESULT enemy::init(float x, float y)
{
	{
		_move	 = new enemyMoveState();
		_run	 = new enemyRunState();
		_attack	 = new enemyAttackState();
		_hit	 = new enemyHitState();
		_down	 = new enemyDownState();
		_dizzy	 = new enemyDizzyState();
		_dead	 = new enemyDeadState();
	}

	addImage();

	_x = x;
	_y = y;
	_width = 130;
	_height = 200;

	_rc = RectMakeCenter(_x, _y, _width, _height);
	_shadow = RectMakeCenter(_x, _y + 100, 50, 30);

	_image = IMAGEMANAGER->findImage("boy_walk");

	_right = _isHit = false;
	_jumpPower = _gravity = 0;
	_state = _move;

	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	_y -= _jumpPower;
	_jumpPower -= _gravity;

	_rc = RectMakeCenter(_x, _y, _width, _height);
	_shadow = RectMakeCenter(_x, _y + 100, 80, 30);

	_state->update(*this, _playerRC, _playerX, _playerY, ENEMYTYPE::BOY);

	if (_isLay) _layCount++;

	//pixelCollision();

	//if (_hitCount == 1) _hitState = HITSTATE::HIT1;
	//if (_hitCount == 2) _hitState = HITSTATE::HIT2;
	//if (_hitCount == 3) _hitState = HITSTATE::HIT3;

	//CAMERAMANAGER->setX(_x);
	//CAMERAMANAGER->setY(_y);
}

void enemy::render()
{
	draw();

	CAMERAMANAGER->renderRectangle(getMemDC(), _attackRC);
	//CAMERAMANAGER->renderRectangle(getMemDC(), _rc);
	CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("enemy_shadow"), _x, _shadow.top + IMAGEMANAGER->findImage("enemy_shadow")->getHeight() / 2);
	CAMERAMANAGER->renderRectangle(getMemDC(), _shadow);
	CAMERAMANAGER->frameRender(getMemDC(), _image, _x , _y , _currentX, _currentY);
}

void enemy::directionCheck(RECT rc, float x, float y)
{
	_playerRC = rc;
	_playerX = x;
	_playerY = y;

	//방향 체크
	if (x > _x)
	{
		_right = true;
	}

	if (x < _x)
	{
		_right = false;
	}

	//거리 체크
	if (getDistance(x, y, _x, _y) < 200) _condition = CONDITION::CLOSE;
	if (getDistance(x, y, _x, _y) > 200) _condition = CONDITION::SEARCH;
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
	for (int i = _probeU - 10; i < _probeU + 5; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("background")->getMemDC(), (_shadow.right + _shadow.left) / 2, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);


		if (r == 255 && g == 0 && b == 0) 
		{
			_probeU -= i;
		}

		if (r == 255 && g == 255 && b == 0)
		{

		}
	}

	//아래
	for (int i = _probeB - 5; i < _probeB + 10; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("background")->getMemDC(), (_shadow.right + _shadow.left) / 2, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 255)
		{
			
		}

		if (r == 255 && g == 255 && b == 0)
		{

		}
	}

	//왼쪽
	for (int i = _probeL - 5; i < _probeL + 5; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("background")->getMemDC(), i, (_shadow.top + _shadow.bottom) / 2);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 255)
		{

		}

		if (r == 255 && g == 255 && b == 0)
		{

		}
	}

	//오른쪽
	for (int i = _probeR - 5; i < _probeR + 5; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("background")->getMemDC(), i, (_shadow.top + _shadow.bottom) / 2);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 255)
		{
			
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
	IMAGEMANAGER->addImage("enemy_shadow", "image/enemy/enemy_shadow.bmp", 128, 38, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("boy_idle", "image/enemy/boy_idle.bmp", 1224, 432, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boy_walk", "image/enemy/boy_walk.bmp", 1620, 444, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boy_run", "image/enemy/boy_run.bmp", 1920, 390, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boy_attack1", "image/enemy/boy_attack1.bmp", 1764, 426, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boy_attack2", "image/enemy/boy_attack2.bmp", 1386, 510, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boy_attack3", "image/enemy/boy_attack3.bmp", 1863, 558, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boy_sidekick", "image/enemy/boy_sidekick.bmp", 1764, 444, 7, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("boy_hit", "image/enemy/boy_gethit.bmp", 1728, 450, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boy_hit1", "image/enemy/boy_hit1.bmp", 576, 450, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boy_hit2", "image/enemy/boy_hit2.bmp", 576, 450, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boy_hit3", "image/enemy/boy_hit3.bmp", 576, 450, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boy_groundhit", "image/enemy/boy_groundhit.bmp", 690, 127, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boy_knockdown", "image/enemy/boy_knockdown.bmp", 8910, 420, 33, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boy_dizzy", "image/enemy/boy_dizzy.bmp", 633, 408, 4, 2, true, RGB(255, 0, 255));
}
