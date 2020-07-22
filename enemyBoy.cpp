#include "stdafx.h"
#include "enemyBoy.h"

void enemyBoy::update()
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

//void enemyBoy::type()
//{
//	_state->update(*this, _playerRC, _playerX, _playerY, ENEMYTYPE::BOY);
//}
