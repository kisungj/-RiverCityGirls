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
		_move = new enemyMoveState();
		_attack = new enemyAttackState();
		_guard = new enemyGuardState();
		_hit = new enemyHitState();
		_down = new enemyDownState();
		_beg = new enemyBegState();
		_dizzy = new enemyDizzyState();
	}

	addImage();

	_x = 300;
	_y = WINSIZEY / 2;
	_width = 130;
	_height = 200;

	_rc = RectMakeCenter(_x, _y, _width, _height);
	_shadow = RectMakeCenter(_x, _y + 100, _width, 30);

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
	_shadow = RectMakeCenter(_x, _y + 100, _width, 30);

	_state->update(*this, _playerRC, _playerX, _playerY, ENEMYTYPE::BOY);

	cout << _hitCount << ", " << _isHit << endl;
	//cout << _jumpPower << ", " << _gravity << endl;
}

void enemy::render()
{
	draw();

	CAMERAMANAGER->renderRectangle(getMemDC(), _rc);
	CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("enemy_shadow"), _shadow.left, _shadow.top);
	CAMERAMANAGER->frameRender(getMemDC(), _image, _x - _image->getFrameWidth() / 2, _y - _image->getFrameHeight() / 2, _currentX, _currentY);
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

	//1단 맞기 프레임 0~2, 2단 맞기 3~5, 3단 맞기 6~8 (반대로 8~6, 5~3, 2~0)
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
	//1단 맞기 프레임 0~2, 2단 맞기 3~5, 3단 맞기 6~8 (반대로 8~6, 5~3, 2~0)
	IMAGEMANAGER->addFrameImage("boy_hit", "image/enemy/boy_gethit.bmp", 1728, 450, 9, 2, true, RGB(255, 0, 255));
	// 24, 8
	IMAGEMANAGER->addFrameImage("boy_knockdown", "image/enemy/boy_knockdown.bmp", 8910, 420, 33, 2, true, RGB(255, 0, 255));

	//int boyRightIdle[] = { 0,1,2,3,4,5,6,7 };
	//KEYANIMANAGER->addArrayFrameAnimation("boy_rightIdle", "boy_idle", boyRightIdle, 8, 10, true);

	//int boyLeftIdle[] = { 15,14,13,12,11,10,9,8, };
	//KEYANIMANAGER->addArrayFrameAnimation("boy_leftIdle", "boy_idle", boyLeftIdle, 8, 10, true);

	//int boyRightWalk[] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
	//KEYANIMANAGER->addArrayFrameAnimation("boy_rightWalk", "boy_walk", boyRightWalk, 12, 10, true);

	//int boyLeftWalk[] = { 23,22,21,20,19,18,17,16,15,14,13,12 };
	//KEYANIMANAGER->addArrayFrameAnimation("boy_leftWalk", "boy_walk", boyLeftWalk, 12, 10, true);

	//int boyRightRun[] = { 0,1,2,3,4,5,6,7,8,9 };
	//KEYANIMANAGER->addArrayFrameAnimation("boy_rightRun", "boy_run", boyRightRun, 10, 10, true);

	//int boyLeftRun[] = { 19,18,17,16,15,14,13,12,11,10 };
	//KEYANIMANAGER->addArrayFrameAnimation("boy_leftRun", "boy_run", boyLeftRun, 10, 10, true);

	//int boyRightAttack1[] = { 0,1,2,3,4,5,6 };
	//KEYANIMANAGER->addArrayFrameAnimation("boy_rightAttack1", "boy_attack1", boyRightAttack1, 7, 10, false);

	//int boyLeftAttack1[] = { 13,12,11,10,9,8,7 };
	//KEYANIMANAGER->addArrayFrameAnimation("boy_leftAttack1", "boy_attack1", boyLeftAttack1, 7, 10, false);

	//int boyRightAttack2[] = { 0,1,2,3,4,5,6 };
	//KEYANIMANAGER->addArrayFrameAnimation("boy_rightAttack2", "boy_attack2", boyRightAttack2, 7, 10, false);

	//int boyLeftAttack2[] = { 13,12,11,10,9,8,7 };
	//KEYANIMANAGER->addArrayFrameAnimation("boy_leftAttack2", "boy_attack2", boyLeftAttack2, 7, 10, false);

	//int boyRightAttack3[] = { 0,1,2,3,4,5,6,7,8 };
	//KEYANIMANAGER->addArrayFrameAnimation("boy_rightAttack3", "boy_attack3", boyRightAttack3, 9, 10, false);

	//int boyLeftAttack3[] = { 17,16,15,14,13,12,11,10,9 };
	//KEYANIMANAGER->addArrayFrameAnimation("boy_leftAttack3", "boy_attack3", boyLeftAttack3, 9, 10, false);

	//int boyRightHit[] = { 0,1,2,3,4,5,6,7,8 };
	//KEYANIMANAGER->addArrayFrameAnimation("boy_rightHit", "boy_hit", boyRightHit, 9, 10, false);

	//int boyLeftHit[] = { 17,16,15,14,13,12,11,10,9 };
	//KEYANIMANAGER->addArrayFrameAnimation("boy_leftHit", "boy_hit", boyLeftHit, 9, 10, false);

	//int boyRightDown[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32 };
	//KEYANIMANAGER->addArrayFrameAnimation("boy_rightDown", "boy_knockdown", boyRightDown, 33, 10, false);

	//int boyLeftDown[] = { 43,42,41,40,39,38,37,36,35,34,33,54,53,52,51,50,49,48,47,46,45,44,65,64,63,62,61,60,59,58,57,56,55};
	//KEYANIMANAGER->addArrayFrameAnimation("boy_leftdown", "boy_knockdown", boyLeftDown, 33, 10, false);

}
