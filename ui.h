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
	RECT _hpRC;
	RECT _bossHpRc;
	tagInvenUi _inventory[10];

	int _itemSelectIndex;

	float _timer;

	float _phoneAlpha;
	float _hpWidth;
	float _bossHpWidth;

	bool _isPhone;
	bool _isUse;
	bool _select;
	bool _isBossStage;

	bool _useHP;
	bool _usePower;


public:
	ui() {}
	~ui() {}
public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();

	void setHpGauge(float curHp, float maxHp);
	void setBossHpGauge(float curHp, float maxHp);
	void setBossStage(bool arg) { _isBossStage = arg; }

	bool getIsPhone() { return _isPhone; }
	bool getUseHP() { return _useHP; }
	bool getUsePower() { return _usePower; }
	void setUseHP(bool arg) { _useHP = arg; }
	void setUsePower(bool arg) { _usePower = arg; }

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

	void setEquipInventoryUI(Item* item)
	{
		for (int i = 0; i < 2; i++)
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

