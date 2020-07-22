#pragma once
#include "gameNode.h"
#include "item.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

struct tagInvenUi
{
	RECT rc;
	Item* item;

	bool isNull;
};

class ui : public gameNode
{
private:
	image* _hpUI;
	image* _selectArrow;
	image* _loading;
	RECT _hpRC;
	tagInvenUi _inventory[10];

	int _itemSelectIndex;

	float _timer;

	float _phoneAlpha;
	float _hpWidth;
	

	bool _isPhone;

public:
	ui() {}
	~ui() {}
public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();

	void setHpGauge(float curHp, float maxHp);
	bool getIsPhone() { return _isPhone; }

	void setInventoryUI(Item* item) 
	{
		for (int i = 2; i < 10; i++)
		{
			if (_inventory[i].isNull)
			{
				_inventory[i].item = item;
				_inventory[i].isNull = false;
				break;
			}
		}
	}
};

