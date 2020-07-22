#include "stdafx.h"
#include "inventory.h"

inventory::inventory()
{
}

inventory::~inventory()
{
}

HRESULT inventory::init()
{
	_inItemName = "";
	_inItemDiscription = "";
	_inHpPortion = 0;
	_inPowerPortion = 0;

	return S_OK;
}

void inventory::release()
{
}

void inventory::update()
{
	for (int i = 0; i < vInventory.size(); ++i)
	{
		cout << vInventory[i]->getItemName() << endl;
		cout << vInventory.size() << endl;
	}
}

void inventory::render()
{
	char str[256];
	sprintf_s(str, "아이템이름 : %s", _inItemName.c_str());
	TextOut(getMemDC(), 50, 200, str, strlen(str));

	sprintf_s(str, "아이템설명 : %s", _inItemDiscription.c_str());
	TextOut(getMemDC(), 50, 220, str, strlen(str));

	sprintf_s(str, "HP 증가량 : %d", _inHpPortion);
	TextOut(getMemDC(), 50, 240, str, strlen(str));

	sprintf_s(str, "공격력 증가량 : %d", _inPowerPortion);
	TextOut(getMemDC(), 50, 260, str, strlen(str));
}
