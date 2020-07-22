#include "stdafx.h"
#include "Item.h"

Item::Item()
{
}

Item::~Item()
{
}

HRESULT Item::init(ITEMSTATE itemstate)
{
	_itemState = itemstate;

	switch (_itemState)
	{
	case HP:
		_itemImg = IMAGEMANAGER->findImage("물약1");
		_itemName = "HP포션";
		_itemDiscription = "체력을 30만큼 회복시켜준다.";
		_hpPortion = 30;
		break;

	case POWER:
		_itemImg = IMAGEMANAGER->findImage("물약2");
		_itemName = "파워포션";
		_itemDiscription = "공격력을 20만큼 증가시켜준다.";
		_powerPortion = 20;
		break;

	case GOLD:
		_itemImg = IMAGEMANAGER->findImage("금동전");
		break;


	case SILVER:
		_itemImg = IMAGEMANAGER->findImage("은동전");
		break;
	}

	return S_OK;
}

HRESULT Item::init(ITEMSTATE itemstate, POINT position)
{
	_itemState = itemstate;

	switch (_itemState)
	{
	case HP:
		_itemImg = IMAGEMANAGER->findImage("물약1");
		_itemName = "HP포션";
		_itemDiscription = "체력을 30만큼 회복시켜준다.";
		_hpPortion = 30;
		break;

	case POWER:
		_itemImg = IMAGEMANAGER->findImage("물약2");
		_itemName = "파워포션";
		_itemDiscription = "공격력을 20만큼 증가시켜준다.";
		_powerPortion = 20;
		break;

	case GOLD:
		_itemImg = IMAGEMANAGER->findImage("금동전");
		break;


	case SILVER:
		_itemImg = IMAGEMANAGER->findImage("은동전");
		break;
	}

	_x = position.x;
	_y = position.y;
	_gravity = 20.0f;
	_itemRc = RectMakeCenter(_x, _y, _itemImg->getWidth(), _itemImg->getHeight());

	_gravityBool = true;

	return S_OK;
}

void Item::update()
{
	move();
	_itemRc = RectMakeCenter(_x, _y, _itemImg->getWidth(), _itemImg->getHeight());
}

void Item::release()
{
}

void Item::render()
{
	CAMERAMANAGER->render(getMemDC(), _itemImg, _x,_y);

	if (KEYMANAGER->isToggleKey('V'))
	{
		CAMERAMANAGER->renderRectangle(getMemDC(), _itemRc);
	}
}

//아이템 드랍시 떨어지게
void Item::move()
{
	//중력값 켜지면 일정거리로 떨어짐
	if (_gravityBool)
	{
		_y += _gravity;
		_gravity--;

		if (_gravity == 0)
		{
			_gravityBool = false;
		}
	}

	//중력값 꺼지면 멈춤
	if (!_gravityBool)
	{
		_gravity = 0;
	}
}
