#include "stdafx.h"
#include "Item.h"

Item::Item()
{
}

Item::~Item()
{
}

HRESULT Item::init(ITEMSTATE itemstate, POINT position)
{
	_itemState = itemstate;

	switch (_itemState)
	{
	case HP:
		_itemImg = IMAGEMANAGER->findImage("����1");
		_name = "HP����";
		_discription = "ü���� 30��ŭ ȸ�������ش�.";
		_hpAmount = 30;
		break;

	case POWER:
		_itemImg = IMAGEMANAGER->findImage("����2");
		_name = "�Ŀ�����";
		_discription = "���ݷ��� 20��ŭ ���������ش�.";
		_attackAmount = 20;
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
	_gravity = 15.0f;
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
	CAMERAMANAGER->render(getMemDC(), _itemImg, (_itemRc.left, +_itemRc.right) / 2, (_itemRc.bottom + _itemRc.top) / 2);

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
