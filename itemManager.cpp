#include "stdafx.h"
#include "ItemManager.h"

itemManager::itemManager()
{
}

itemManager::~itemManager()
{
}

HRESULT itemManager::init()
{
	_itemMove = false;

	return S_OK;
}

void itemManager::release()
{
	for (int i = 0; i < _vItems.size(); i++)
	{
		SAFE_DELETE(_vItems[i]);
	}
	_vItems.clear();
}

void itemManager::update()
{
	for (int i = 0; i < _vItems.size(); i++)
	{
		_vItems[i]->update();
	}
}

void itemManager::render()
{
	for (int i = 0; i < _vItems.size(); i++)
	{
		_vItems[i]->render();
	}
}

void itemManager::setItem(RECT rc)
{
	//�������༭ Ȯ�� ���ϱ�
	int rnditempercent = RND->getInt(100);

	//���� if���� 25�� Ȯ���� ������ �������� �ٸ�
	if (rnditempercent >= 0 && rnditempercent <= 25)
	{
		Item* _item = new Item;

		if(!_itemMove)
		{
			_item->init(HP, PointMake((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2));
		}

		if (_itemMove)
		{
			_item->init(HP, PointMake((rc.left + rc.right) / 2, rc.top - 130));
		}
		_vItems.push_back(_item);
	}

	if (rnditempercent >= 26 && rnditempercent <= 50)
	{
		Item* _item = new Item;

		if (!_itemMove)
		{
			_item->init(POWER, PointMake((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2));
		}

		if (_itemMove)
		{
			_item->init(POWER, PointMake((rc.left + rc.right) / 2, rc.top - 130));
		}
		
		_vItems.push_back(_item);
	}

	if (rnditempercent >= 51 && rnditempercent <= 75)
	{
		Item* _item = new Item;

		if (!_itemMove)
		{
			_item->init(GOLD, PointMake((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2));
		}

		if (_itemMove)
		{
			_item->init(GOLD, PointMake((rc.left + rc.right) / 2, rc.top - 130));
		}

		_vItems.push_back(_item);
	}

	if (rnditempercent >= 76 && rnditempercent <= 100)
	{
		Item* _item = new Item;

		if (!_itemMove)
		{
			_item->init(SILVER, PointMake((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2));
		}

		if (_itemMove)
		{
			_item->init(SILVER, PointMake((rc.left + rc.right) / 2, rc.top - 130));
		}

		_vItems.push_back(_item);
	}
}

//������ �浹�� ����
void itemManager::removeItem(int index)
{
	_vItems.erase(_vItems.begin() + index);
}
