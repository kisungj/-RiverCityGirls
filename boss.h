#pragma once
#include "gameNode.h"

enum STATEBOSS
{
	BOSS_LEFT_IDLE,       BOSS_RIGHT_IDLE,
	BOSS_LEFT_WALK,       BOSS_RIGHT_WALK,
	BOSS_LEFT_HIT,        BOSS_RIGHT_HIT,
	BOSS_LEFT_HIT_GETUP,  BOSS_RIGHT_HIT_GETUP,
	BOSS_LEFT_ATTACK,     BOSS_RIGHT_ATTACK,
	BOSS_LEFT_DEATH,      BOSS_RIGHT_DEATH,
	BOSS_LEFT_BLOCK,      BOSS_RIGHT_BLOCK,
	BOSS_LEFT_
};


class boss : public gameNode
{
private:		
	float      _x, _y;                 // ���� �߽���
	float      _jumpPower, _gravity;   // ���� ���� ���� ����		
	STATEBOSS  _state;                 // ���� ���� �����
	RECT       _rc;                    // ���� �浹 ��Ʈ
	image*     _img;                   // ���� �̹���
		
public:
	boss() {}
	~boss() {}
public:
	HRESULT init();
	void    release();
	void    render();
	void    update();
};

