#pragma once
#include "gameNode.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
class player;
enum STATEBOSS
{
	BOSS_LEFT_IDLE, BOSS_RIGHT_IDLE,          // �⺻ ����                          
	BOSS_LEFT_WALK, BOSS_RIGHT_WALK,          // �ȴ� ����						
	BOSS_LEFT_DASH, BOSS_RIGHT_DASH,          // �뽬 ����	 1					
	BOSS_LEFT_TAUNT, BOSS_RIGHT_TAUNT,         // ���							
	BOSS_LEFT_HIT1, BOSS_RIGHT_HIT1,		  // �¾��� �� 1Ÿ					
	BOSS_LEFT_HIT2, BOSS_RIGHT_HIT2,		  // �¾��� �� 2Ÿ					
	BOSS_LEFT_HIT3, BOSS_RIGHT_HIT3,		  // �¾��� �� 3Ÿ					
	BOSS_LEFT_HIT_GETUP, BOSS_RIGHT_HIT_GETUP,	  // �¾��� �� �Ͼ�� ����			
	BOSS_LEFT_BLOCK, BOSS_RIGHT_BLOCK,	      // ����                              
	BOSS_LEFT_ROAR, BOSS_RIGHT_ROAR,	      // �¾��� �� �� �������� �Լ�		
	BOSS_LEFT_ATTACK, BOSS_RIGHT_ATTACK,		  // �� ����							
	BOSS_LEFT_ATTACK_ELBOW, BOSS_RIGHT_ATTACK_ELBOW,  // ������ ����						
	BOSS_LEFT_JUMP, BOSS_RIGHT_JUMP,          // ����							
	BOSS_LEFT_JUMP_ATTACK, BOSS_RIGHT_JUMP_ATTACK,   // ���� ����						
	BOSS_LEFT_HEAVY_ATTACK, BOSS_RIGHT_HEAVY_ATTACK,  // �� ����							
	BOSS_LEFT_DEATH, BOSS_RIGHT_DEATH,		  // �׾��� ��						
	BOSS_LEFT_DEATH_LOOP, BOSS_RIGHT_DEATH_LOOP,	  // �׾��� �� ����					
	BOSS_LEFT_ANGRY, BOSS_RIGHT_ANGRY,         // ȭ��							
	BOSS_END,
};


class boss : public gameNode
{
private:
	float      _x, _y, _z;                                 // ���� �߽���
	float      _jumpPower, _gravity;                       // ���� ���� ���� ����		
	float      _angle;                                     // ������ �̵� ����
	STATEBOSS  _state;                                     // ���� ���� �����
	RECT       _rc;                                        // ���� �浹 ��Ʈ
	image*     _characterImg;                              // ���� �̹���
	image*     _shadowImg;			                       // ���� �׸��� �̹���
	animation* _anim[BOSS_END];                            // �ִϸ��̼� �����
	animation* _animPlayer;                                // �ִϸ��̼� �÷��̿�
	int        _delayTime;                                 // ���� �� �����̽ð�
	bool       _isDelayTime;                               // ������ �ð�����?      
	int        _patternNumber;                             // ���� ���� ��ȣ
	int        _jumpAndDownAttackCount;                    // ������ ������ ī��Ʈ
	int        _jumpAlpha, _jumpAlphaMin, _jumpAlphaMax;   // ������ �� �׸��� ���İ� ����
	int        _hitDelay, _hitCount, _hitAndWaitCount;     // �¾��� �� ������, ��� �¾Ҵ��� ī��Ʈ, 3�� �°��� ���� �� ���
	float      _blockDistance, _blockFriction;             // ������ �� �и��� �Ÿ�, �и��°Ÿ����� ������ ���ش�.

	// ----- ���� ���� ���� ----- //
	RECT       _attackRect;                                // ���� ����
	MYPOINT    _attackPos;                                 // ���� ���� ��ġ
	MYPOINT    _attackSize;                                // ���� ���� ������
	bool       _isColision;                                // ��ø���� �ȵ����� ������
	int        _attackCount;                               // ��ø ������
	int        _damege;
	// ----------------- ���� ���� ���� ----------------- //
	int        _hp, _maxHp;
	float      _applySpeed;
	int        _phaseCount;
	// ----------------- ���� ���� ���� ----------------- //

	// ----------------- �ȼ� �浹 ���� ----------------- //
	COLORREF _colorF;
	int      _probeLeft, _probeRight, _probeUp, _probeDown;
	int      _r, _g, _b;
	bool     _isPixelCollision;
	// ----------------- �ȼ� �浹 ���� ----------------- //

	player* _player;

	// --------------- ī�޶� ���� ���� ----------------- //
	bool _isShake;
	int  _shakePower;
	int  _shakeTime;
	// --------------- ī�޶� ���� ���� ----------------- //



public:
	boss() {}
	~boss() {}
public:
	HRESULT init();
	void    release();
	void    render();
	void    update(float playerX, float playerZ);
public:
	void    loadAnimation();            // ���� �ִϸ��̼� �ε�
	void    stateUpdate(float playerX, float playerZ);              // ���� ������Ʈ ������Ʈ.
public:
	void    attack(float playerX, float playerZ);                   // �÷��̾ ã�Ƽ� �� ����
	void    heavyAttack(float playerX, float playerZ);              // �÷��̾ ã�Ƽ� �� ����
	void    dashAttack(float playerX, float playerZ);               // �뽬  ����
	void    jumpAttack(float playerX, float playerZ);               // ����  ����
	void    elbowAttack(float playerX, float playerZ);              // ������ ����
	void    changePattern(float playerX, float playerZ);            // ���� �ٲٴ¿�
	void    death(float playerX, float playerZ);                    // ���� ����
	void    hit(float playerX, float playerZ, int damege);          // �浹 ���� --> �Űܾ���
	void    toPlayerCollision();                                    // �÷��̾� ������ ����
	void    pixelCollision();                                       // �ȼ� �浹
	void    shakeCamera(int power, int time);                       // ī�޶� ����, �ð�
	void    soundAndCamShakeControl();
public:
	STATEBOSS getState() { return _state; }
	RECT*     getPointerRect() { return &_rc; }
	RECT      getRect() { return _rc; }
	RECT      getAttackRect() { return _attackRect; }
	float     getBossZ() { return _z; }
	int       getHP() { return _hp; }
	int       getMaxHP() { return _maxHp; }
	// -------- ī�޶� getter
	int       getShakePower() { return _shakePower; }
	bool      getIsShake() { return _isShake; }
	int       getShakeTime() { return _shakeTime; }
public:
	void      setIsShake(bool onoff) { _isShake = onoff; }
public:
	void      setPlayerMemoryAddressLink(player* player) { _player = player; }
};

