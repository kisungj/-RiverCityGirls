#pragma once
#include "gameNode.h"
#include "enemyBoy.h"
#include "enemyGirl.h"

class player;

class enemyManager : public gameNode
{
	typedef vector<enemy*> getVEnemy;
	typedef vector<enemy*>::iterator getVIEnemy;
private:
	player* _player;

	getVEnemy _vBoy;
	getVIEnemy _viBoy;

	getVEnemy _vGirl;
	getVIEnemy _viGirl;

	bool _isCollision;							//충돌용
	int _attackCount;							//충돌카운트
public:
	enemyManager() {}
	~enemyManager() {}

	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();

	void setStage1();							//스테이지1 에너미
	void setStage2();							//스테이지2 에너미

	void boyPlCollision();						//플레이어와 남자애 충돌 함수
	void girlPlCollision();						//플레이어와 여자애
	void cheerPlCollision();					//플레이어와 치어리더

	void eraseBoy(int arrNum);
	void eraseGirl(int arrNum);
	void eraseCheer(int arrNum);

	void setPlayerLink(player* player) { _player = player; }

public:
	vector<enemy*> getVBoy() { return _vBoy; }
	vector<enemy*>::iterator getVIBoy() { return _viBoy; }


	vector<enemy*> getVGirl() { return _vGirl; }
	vector<enemy*>::iterator getVIGirl() { return _viGirl; }

};

