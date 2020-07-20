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
	float      _x, _y;                 // 보스 중심점
	float      _jumpPower, _gravity;   // 보스 점프 관련 변수		
	STATEBOSS  _state;                 // 보스 상태 저장용
	RECT       _rc;                    // 보스 충돌 렉트
	image*     _img;                   // 보스 이미지
		
public:
	boss() {}
	~boss() {}
public:
	HRESULT init();
	void    release();
	void    render();
	void    update();
};

