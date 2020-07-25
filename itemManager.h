#pragma once
#include "gameNode.h"
#include "Item.h"
#include <vector>

class itemManager : public gameNode
{
private:
	typedef vector<Item*>				vItem;
	typedef vector<Item*>::iterator		viItem;

private:
	vItem _vItems;

	bool _itemMove;

public:
	itemManager();
	~itemManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setItem(RECT rc);
	void removeItem(int index);


	vector<Item*> getVItem() { return _vItems; }		//아이템 벡터값
	bool getItemMove() { return _itemMove; }
	void setItemMove(bool move) { _itemMove = move; }
};

