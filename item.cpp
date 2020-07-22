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
		_itemImg = IMAGEMANAGER->findImage("����1");
		_itemName = "HP����";
		_itemDiscription = "ü���� 30��ŭ ȸ�������ش�.";
		_hpPortion = 30;
		break;

	case POWER:
		_itemImg = IMAGEMANAGER->findImage("����2");
		_itemName = "�Ŀ�����";
		_itemDiscription = "���ݷ��� 20��ŭ ���������ش�.";
		_powerPortion = 20;
		break;

	case GOLD:
		_itemImg = IMAGEMANAGER->findImage("�ݵ���");
		break;


	case SILVER:
		_itemImg = IMAGEMANAGER->findImage("������");
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
		_itemImg = IMAGEMANAGER->findImage("����1");
		_itemName = "HP����";
		_itemDiscription = "ü���� 30��ŭ ȸ�������ش�.";
		_hpPortion = 30;
		break;

	case POWER:
		_itemImg = IMAGEMANAGER->findImage("����2");
		_itemName = "�Ŀ�����";
		_itemDiscription = "���ݷ��� 20��ŭ ���������ش�.";
		_powerPortion = 20;
		break;

	case GOLD:
		_itemImg = IMAGEMANAGER->findImage("�ݵ���");
		break;


	case SILVER:
		_itemImg = IMAGEMANAGER->findImage("������");
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

//������ ����� ��������
void Item::move()
{
	//�߷°� ������ �����Ÿ��� ������
	if (_gravityBool)
	{
		_y += _gravity;
		_gravity--;

		if (_gravity == 0)
		{
			_gravityBool = false;
		}
	}

	//�߷°� ������ ����
	if (!_gravityBool)
	{
		_gravity = 0;
	}
}
