#pragma once
#include "gameNode.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
class player;
enum STATEBOSS
{
	BOSS_LEFT_IDLE, BOSS_RIGHT_IDLE,          // 기본 상태                          
	BOSS_LEFT_WALK, BOSS_RIGHT_WALK,          // 걷는 상태						
	BOSS_LEFT_DASH, BOSS_RIGHT_DASH,          // 대쉬 공격	 1					
	BOSS_LEFT_TAUNT, BOSS_RIGHT_TAUNT,         // 놀리기							
	BOSS_LEFT_HIT1, BOSS_RIGHT_HIT1,		  // 맞았을 때 1타					
	BOSS_LEFT_HIT2, BOSS_RIGHT_HIT2,		  // 맞았을 때 2타					
	BOSS_LEFT_HIT3, BOSS_RIGHT_HIT3,		  // 맞았을 때 3타					
	BOSS_LEFT_HIT_GETUP, BOSS_RIGHT_HIT_GETUP,	  // 맞았을 때 일어나서 공격			
	BOSS_LEFT_BLOCK, BOSS_RIGHT_BLOCK,	      // 막기                              
	BOSS_LEFT_ROAR, BOSS_RIGHT_ROAR,	      // 맞았을 때 다 못때리면 함성		
	BOSS_LEFT_ATTACK, BOSS_RIGHT_ATTACK,		  // 약 공격							
	BOSS_LEFT_ATTACK_ELBOW, BOSS_RIGHT_ATTACK_ELBOW,  // 엘보우 공격						
	BOSS_LEFT_JUMP, BOSS_RIGHT_JUMP,          // 점프							
	BOSS_LEFT_JUMP_ATTACK, BOSS_RIGHT_JUMP_ATTACK,   // 점프 공격						
	BOSS_LEFT_HEAVY_ATTACK, BOSS_RIGHT_HEAVY_ATTACK,  // 강 공격							
	BOSS_LEFT_DEATH, BOSS_RIGHT_DEATH,		  // 죽었을 때						
	BOSS_LEFT_DEATH_LOOP, BOSS_RIGHT_DEATH_LOOP,	  // 죽었을 때 루프					
	BOSS_LEFT_ANGRY, BOSS_RIGHT_ANGRY,         // 화남							
	BOSS_END,
};


class boss : public gameNode
{
private:
	float      _x, _y, _z;                                 // 보스 중심점
	float      _jumpPower, _gravity;                       // 보스 점프 관련 변수		
	float      _angle;                                     // 보스의 이동 각도
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
	int        _hitDelay, _hitCount, _hitAndWaitCount;     // 맞았을 때 딜레이, 몇대 맞았는지 카운트, 3대 맞고나서 공격 전 대기
	float      _blockDistance, _blockFriction;             // 막았을 때 밀리는 거리, 밀리는거리에서 마찰력 빼준다.

	// ----- 공격 관련 변수 ----- //
	RECT       _attackRect;                                // 공격 범위
	MYPOINT    _attackPos;                                 // 공격 범위 위치
	MYPOINT    _attackSize;                                // 공격 범위 사이즈
	bool       _isColision;                                // 중첩으로 안들어오게 막아줌
	int        _attackCount;                               // 중첩 막아줌
	int        _damege;
	// ----------------- 스텟 관련 변수 ----------------- //
	int        _hp, _maxHp;
	float      _applySpeed;
	int        _phaseCount;
	// ----------------- 스텟 관련 변수 ----------------- //

	// ----------------- 픽셀 충돌 변수 ----------------- //
	COLORREF _colorF;
	int      _probeLeft, _probeRight, _probeUp, _probeDown;
	int      _r, _g, _b;
	bool     _isPixelCollision;
	// ----------------- 픽셀 충돌 변수 ----------------- //

	player* _player;

	// --------------- 카메라 관련 변수 ----------------- //
	bool _isShake;
	int  _shakePower;
	int  _shakeTime;
	// --------------- 카메라 관련 변수 ----------------- //



public:
	boss() {}
	~boss() {}
public:
	HRESULT init();
	void    release();
	void    render();
	void    update(float playerX, float playerZ);
public:
	void    loadAnimation();            // 보스 애니메이션 로드
	void    stateUpdate(float playerX, float playerZ);              // 보스 스테이트 업데이트.
public:
	void    attack(float playerX, float playerZ);                   // 플레이어를 찾아서 약 공격
	void    heavyAttack(float playerX, float playerZ);              // 플레이어를 찾아서 강 공격
	void    dashAttack(float playerX, float playerZ);               // 대쉬  공격
	void    jumpAttack(float playerX, float playerZ);               // 점프  공격
	void    elbowAttack(float playerX, float playerZ);              // 엘보우 공격
	void    changePattern(float playerX, float playerZ);            // 패턴 바꾸는용
	void    death(float playerX, float playerZ);                    // 죽음 판정
	void    hit(float playerX, float playerZ, int damege);          // 충돌 판정 --> 옮겨야함
	void    toPlayerCollision();                                    // 플레이어 때리는 판정
	void    pixelCollision();                                       // 픽셀 충돌
	void    shakeCamera(int power, int time);                       // 카메라 강도, 시간
	void    soundAndCamShakeControl();
public:
	STATEBOSS getState() { return _state; }
	RECT*     getPointerRect() { return &_rc; }
	RECT      getRect() { return _rc; }
	RECT      getAttackRect() { return _attackRect; }
	float     getBossZ() { return _z; }
	int       getHP() { return _hp; }
	int       getMaxHP() { return _maxHp; }
	// -------- 카메라 getter
	int       getShakePower() { return _shakePower; }
	bool      getIsShake() { return _isShake; }
	int       getShakeTime() { return _shakeTime; }
public:
	void      setIsShake(bool onoff) { _isShake = onoff; }
public:
	void      setPlayerMemoryAddressLink(player* player) { _player = player; }
};

