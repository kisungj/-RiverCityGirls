#include "stdafx.h"
#include "boss.h"

HRESULT boss::init()
{
	// ------------ 임시 변수 ------------ //
	_x = _y = _jumpPower = _gravity = 0;
	_state = BOSS_LEFT_IDLE;
	_rc = RectMakeCenter(_x, _y, 100, 100);
	

	// ------------ 임시 변수 ------------ //
	return S_OK;
}

void boss::release()
{
}

void boss::render()
{
}

void boss::update()
{
}
