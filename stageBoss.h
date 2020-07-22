#pragma once
#include "gameNode.h"

class stageBoss : public gameNode
{
private:
	class boss*   _boss;
	class player* _player;
	
public:
	stageBoss() {}
	~stageBoss() {}
public:
	virtual HRESULT init(player* player, boss* boss);
	virtual void render();
	virtual void update();
	virtual void release();
public:

};

