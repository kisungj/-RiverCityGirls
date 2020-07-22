#pragma once
#include "gameNode.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")


enum STATEBOSS
{
	BOSS_LEFT_IDLE,         BOSS_RIGHT_IDLE,          // 기본 상태
	BOSS_LEFT_WALK,         BOSS_RIGHT_WALK,          // 걷는 상태
	BOSS_LEFT_DASH,		    BOSS_RIGHT_DASH,          // 대쉬 공격
	BOSS_LEFT_HIT1,         BOSS_RIGHT_HIT1,		  // 맞았을 때 1타
	BOSS_LEFT_HIT2,         BOSS_RIGHT_HIT2,		  // 맞았을 때 2타
	BOSS_LEFT_HIT3,         BOSS_RIGHT_HIT3,		  // 맞았을 때 3타
	BOSS_LEFT_HIT_GETUP,    BOSS_RIGHT_HIT_GETUP,	  // 맞았을 때 일어나서 공격
	BOSS_LEFT_ATTACK,       BOSS_RIGHT_ATTACK,		  // 약 공격
	BOSS_LEFT_ATTACK_ELBOW, BOSS_RIGHT_ATTACK_ELBOW,  // 엘보우 공격
	BOSS_LEFT_JUMP,         BOSS_RIGHT_JUMP,          // 점프
	BOSS_LEFT_JUMP_ATTACK,  BOSS_RIGHT_JUMP_ATTACK,   // 점프 공격
	BOSS_LEFT_HEAVY_ATTACK, BOSS_RIGHT_HEAVY_ATTACK,  // 강 공격
	BOSS_LEFT_DEATH,        BOSS_RIGHT_DEATH,		  // 죽었을 때
	BOSS_LEFT_DEATH_LOOP,   BOSS_RIGHT_DEATH_LOOP,	  // 죽었을 때 루프
	BOSS_LEFT_ANGRY,        BOSS_RIGHT_ANGRY,         // 화남
	BOSS_END,	
};


class boss : public gameNode
{
private:		
	float      _x, _y, _z;                                 // 보스 중심점
	float      _jumpPower, _gravity;                       // 보스 점프 관련 변수		
	float      _angle;                                     // 보스의 이동 각도
	float      _applySpeed;                                // 적용 스피드
	STATEBOSS  _state;                                     // 보스 상태 저장용
	RECT       _rc;                                        // 보스 충돌 렉트
	image*     _characterImg;                              // 보스 이미지
	image*     _shadowImg;			                       // 보스 그림자 이미지
	animation* _anim[BOSS_END];                            // 애니메이션 저장용
	animation* _animPlayer;                                // 애니메이션 플레이용
	int        _delayTime;                                 // 공격 후 딜레이시간
	bool       _isDelayTime;                               // 딜레이 시간인지?      
	int        _patternNumber;                             // 지금 패턴 번호
	int        _jumpAndDownAttackCount;                    // 밑으로 내려올 카운트
	int        _jumpAlpha, _jumpAlphaMin, _jumpAlphaMax;   // 점프할 때 그림자 알파값 조정
	int        _hitDelay,  _hitCount;                      // 맞았을 때 딜레이, 몇대 맞았는지 카운트
	// ----------------- 스텟 관련 변수 -----------------//
	int        _hp, maxHp;
	int        _damage;
	// ----------------- 스텟 관련 변수 -----------------//

	// ================= 임시 변수 삭제하세요 ================= //
	RECT       _player;
	float      _playerX, _playerY;
	// ================= 임시 변수 삭제하세요 ================= //
	
public:
	boss() {}
	~boss() {}
public:
	HRESULT init();
	void    release();
	void    render();
	void    update();
public:
	void    loadImage();                // 보스 이미지 리소스 로드
	void    loadAnimation();            // 보스 애니메이션 로드
	void    stateUpdate();              // 보스 스테이트 업데이트.
public:
	void    attack(float playerX, float playerZ);                   // 플레이어를 찾아서 약 공격
	void    heavyAttack(float playerX, float playerZ);              // 플레이어를 찾아서 약 공격
	void    dashAttack(float playerX, float playerZ);               // 대쉬 공격
	void    jumpAttack(float playerX, float playerZ);               // 점프 공격
	void    elbowAttack(float playerX, float playerZ);              // 엘보우공격
	void    changePattern();
};

