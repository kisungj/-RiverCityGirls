#pragma once
#include "gameNode.h"
#include "enemyBoy.h"
class player;

class enemyManager : public gameNode
{
	typedef vector<enemy*> getVEnemy;
	typedef vector<enemy*>::iterator getVIEnemy;
private:
	getVEnemy _vBoy;
	getVIEnemy _viBoy;
	player* _player;


public:
	enemyManager() {}
	~enemyManager() {}

	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();

	void setBoy();	
	void setGirl();	
	void setCheer();
	void eraseBoy(int arrNum);
	void eraseGirl(int arrNum);
	void eraseCheer(int arrNum);

	void setPlayerLink(player* player) { _player = player; }

public:
	vector<enemy*> getVBoy() { return _vBoy; }
	vector<enemy*>::iterator getVIBoy() { return _viBoy; }
};

