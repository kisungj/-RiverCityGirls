#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{

	IMAGEMANAGER->addFrameImage("PLAYER_IDLE", "image/player/Kyoko_Idle.bmp", 1440, 450, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_WALK", "image/player/Kyoko_Walk.bmp", 1476, 402, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_RUN", "image/player/Kyoko_Run.bmp", 2736, 384, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_JUMP", "image/player/Kyoko_Jump.bmp", 405, 414, 3, 2, true, RGB(255, 0, 255));


	_idle = new idleState();
	_move = new moveState();
	_jump = new jumpState();

	_state = _idle;
	_img = IMAGEMANAGER->findImage("PLAYER_IDLE");

	_shadowX = WINSIZEX / 2;
	_shadowY = WINSIZEY / 2 + 100;
	_playerX = _shadowX;
	_playerY = _shadowY - 110;
	int rightIdle[] = { 12,13,14,15,16,17,18,19,20,21,22,23 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_IDLE", "PLAYER_IDLE", rightIdle, 12, 10, true);
	int leftIdle[] = { 11,10,9,8,7,6,5,4,3,2,1,0 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_IDLE", "PLAYER_IDLE", leftIdle, 12, 10, true);
	int rightRun[] = { 12,13,14,15,16,17,18,19,20,21,22,23 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_WALK", "PLAYER_WALK", rightRun, 12, 10, true);
	int leftRun[] = { 11,10,9,8,7,6,5,4,3,2,1,0 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_WALK", "PLAYER_WALK", leftRun, 12, 10, true);
	int rightJump[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_JUMP", "PLAYER_JUMP", rightJump, 1, 3, true);
	int leftJump[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("P_LEFT_JUMP", "PLAYER_JUMP", leftJump, 1, 3, true);
	int rightFall[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_JUMP", "PLAYER_JUMP", rightFall, 1, 3, true);
	int leftFall[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_JUMP", "PLAYER_JUMP", leftFall, 1, 3, true);
	int rightLanding[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_JUMP", "PLAYER_JUMP", rightLanding, 1, 3, true);
	int leftLanding[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation("P_RIGHT_JUMP", "PLAYER_JUMP", leftLanding, 1, 3, true);
	_jumpPower = _gravity = 0;
	_rc = RectMakeCenter(_shadowX, _playerY, 80, 30);
	_player = RectMakeCenter(_playerX, _playerY, _img->getFrameWidth(), _img->getFrameHeight());
	_playerMotion = KEYANIMANAGER->findAnimation("P_RIGHT_IDLE");
	_playerMotion->start();

	_isJumping = false;


	_probeBottom = _rc.bottom;

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	KEYANIMANAGER->update();
	_probeBottom = _rc.bottom;
	_playerX = _shadowX;
	//_playerY = _y - 110;

	_state->update(*this);


	//ÇÈ¼¿Ãæµ¹
	for (int i = _probeBottom - 30; i < _probeBottom + 30; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel1")->getMemDC(), (_rc.right + _rc.left) / 2, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 255)
		{
			_isMove = true;
			_rc.bottom += 10;
			_rc.top += 10;
		}
		else
		{
			_isMove = false;
		}
	}

	//cout << _direction << endl;

	if (!_isMove)
	{
		_shadowY += 3;

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
	//Rectangle(getMemDC(), (_rc.right + _rc.left) / 2 - 10, _probeBottom, _rc.right + _rc.left / 2, _probeBottom + 10);

	CAMERAMANAGER->renderRectangle(getMemDC(), _player);
	CAMERAMANAGER->renderRectangle(getMemDC(), _rc);
	//CAMERAMANAGER->aniRender(getMemDC(), _img, _player.left, _player.top, _playerMotion);
	//Rectangle(getMemDC(), _player);
	//Rectangle(getMemDC(), _rc);
	_img->aniRender(getMemDC(), _player.left, _player.top, _playerMotion);

}


