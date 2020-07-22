#include "stdafx.h"
#include "enemy.h"

enemy::enemy()
{
}

enemy::~enemy()
{
}

HRESULT enemy::init()
{
	{
		_move	 = new enemyMoveState();
		_run	 = new enemyRunState();
		_attack	 = new enemyAttackState();
		_hit	 = new enemyHitState();
		_down	 = new enemyDownState();
		_dizzy	 = new enemyDizzyState();
	}

	addImage();

	_x = 1000;
	_y = WINSIZEY / 2 + 300;
	_width = 130;
	_height = 200;

	_rc = RectMakeCenter(_x, _y, _width, _height);
	_shadow = RectMakeCenter(_x, _y + 100, 50, 30);

	_image = IMAGEMANAGER->findImage("boy_walk");
	//_motion = KEYANIMANAGER->findAnimation("boy_rightIdle");

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

	//type();
	//if (_hitCount == 1) _hitState = HITSTATE::HIT1;
	//if (_hitCount == 2) _hitState = HITSTATE::HIT2;
	//if (_hitCount == 3) _hitState = HITSTATE::HIT3;

	//CAMERAMANAGER->setX(_x);
	//CAMERAMANAGER->setY(_y);

	if (_isLay) _layCount++;
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

	//规氢 眉农
	if (x > _x)
	{
		_right = true;
	}

	if (x < _x)
	{
		_right = false;
	}

	//芭府 眉农
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
