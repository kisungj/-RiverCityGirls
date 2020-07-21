#pragma once
#include "gameNode.h"

enum STATEBOSS
{
	BOSS_LEFT_IDLE,         BOSS_RIGHT_IDLE,         // 기본 상태
	BOSS_LEFT_WALK,         BOSS_RIGHT_WALK,         // 걷는 상태
	BOSS_LEFT_DASH,		    BOSS_RIGHT_DASH,         // 대쉬 공격
	BOSS_LEFT_HIT,          BOSS_RIGHT_HIT,			 // 맞았을 때
	BOSS_LEFT_ATTACK,       BOSS_RIGHT_ATTACK,		 // 약 공격
	BOSS_LEFT_ATTACK_ELBOW, BOSS_RIGHT_ATTACK_ELBOW, // 엘보우 공격
	BOSS_LEFT_JUMP_ATTACK,  BOSS_RIGHT_JUMP_ATTACK,  // 점프 공격
	BOSS_LEFT_HEAVY_ATTACK, BOSS_RIGHT_HEAVY_ATTACK, // 강 공격
	BOSS_LEFT_DEATH,        BOSS_RIGHT_DEATH,		 // 죽었을 때
	BOSS_LEFT_ANGRY,        BOSS_RIGHT_ANGRY,        // 화남
	BOSS_END,	
};


class boss : public gameNode
{
private:		
	float      _x, _y, _z;             // 보스 중심점
	float      _jumpPower, _gravity;   // 보스 점프 관련 변수		
	STATEBOSS  _state;                 // 보스 상태 저장용
	RECT       _rc;                    // 보스 충돌 렉트
	image*     _characterImg;          // 보스 이미지
	image*     _shadowImg;			   // 보스 그림자 이미지
	animation* _anim[BOSS_END];        // 애니메이션 저장용
	animation* _animPlayer;            // 애니메이션 플레이용


	// ============ 임시 변수 ============ //
	float       _playerX, _playerY;
	// ============ 임시 변수 ============ //
	
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
	void    loadAnimation();
	void    think();
};

