#pragma once
#include "gameNode.h"
#include "enemyBoy.h"
#include "enemyGirl.h"
#include "enemyCheer.h"

enum class WAVE
{
	FIRST, SECOND, REPEAT
};

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

	getVEnemy _vCheer;
	getVIEnemy _viCheer;

	int _waveCount;
	int _rnd;
	WAVE _wave;

public:
	enemyManager() {}
	~enemyManager() {}

	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();

	void setStage1();							//��������1 ���ʹ�
	void setStage2();							//��������2 ���ʹ�
	void waveStage1();							//�ð��� ������ ���ʹ� �߰�
	void waveStage2();							//�� ���� ������ ���ʹ� �߰�

	void boyPlCollision();						//�÷��̾�� ���ھ� �浹 �Լ�
	void girlPlCollision();						//�÷��̾�� ���ھ�
	void cheerPlCollision();					//�÷��̾�� ġ���

	void eraseBoy(int arrNum);
	void eraseGirl(int arrNum);
	void eraseCheer(int arrNum);

	void setPlayerLink(player* player) { _player = player; }

public:
	vector<enemy*> getVBoy() { return _vBoy; }
	vector<enemy*>::iterator getVIBoy() { return _viBoy; }


	vector<enemy*> getVGirl() { return _vGirl; }
	vector<enemy*>::iterator getVIGirl() { return _viGirl; }

	vector<enemy*> getVCheer() { return _vCheer; }
	vector<enemy*>::iterator getVICheer() { return _viCheer; }
};

