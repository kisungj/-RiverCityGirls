#pragma once
#include "gameNode.h"
#include "inventory.h"
#include "item.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

struct tagInvenUi
{
	image img;
	RECT rc;
	Item item;
};

class ui : public gameNode
{
private:
	inventory* _inven;

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
};

