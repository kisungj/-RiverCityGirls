#pragma once
#include "gameNode.h"

enum STATEBOSS
{
	BOSS_LEFT_IDLE,         BOSS_RIGHT_IDLE,         // 기본 상태
	BOSS_LEFT_WALK,         BOSS_RIGHT_WALK,         // 걷는 상태
	BOSS_LEFT_HIT,          BOSS_RIGHT_HIT,			 // 맞았을 때
	BOSS_LEFT_HIT_GETUP,    BOSS_RIGHT_HIT_GETUP,	 // 맞고 다시 일어나면서 공격
	BOSS_LEFT_HIT_GROUND,   BOSS_RIGHT_HIT_GROUND,   // 땅에서 플레이어한테 맞았을 때
	BOSS_LEFT_ATTACK,       BOSS_RIGHT_ATTACK,		 // 약 공격
	BOSS_LEFT_HEAVY_ATTACK, BOSS_RIGHT_HEAVY_ATTACK, // 강 공격
	BOSS_LEFT_ATTACK_ELBOW, BOSS_RIGHT_ATTACK_ELBOW, // 엘보우 공격
	BOSS_LEFT_DEATH,        BOSS_RIGHT_DEATH,		 // 죽었을 때
	BOSS_LEFT_BLOCK,        BOSS_RIGHT_BLOCK,		 // 막았을 때
	BOSS_END,	
};


class boss : public gameNode
{
private:		
	float      _x, _y;                 // 보스 중심점
	float      _jumpPower, _gravity;   // 보스 점프 관련 변수		
	STATEBOSS  _state;                 // 보스 상태 저장용
	RECT       _rc;                    // 보스 충돌 렉트
	image*     _img;                   // 보스 이미지

	animation* _anim[BOSS_END];
	animation* _animPlay;
	// ============ 임시 변수 ============ //
	float       _playerX,_playerY;    
public:
	boss() {}
	~boss() {}
public:
	HRESULT init();
	void    release();
	void    render();
	void    update();
public:
	void    loadImage();
};

