#pragma once
#include "gameNode.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")


enum STATEBOSS
{
	BOSS_LEFT_IDLE,         BOSS_RIGHT_IDLE,          // �⺻ ����
	BOSS_LEFT_WALK,         BOSS_RIGHT_WALK,          // �ȴ� ����
	BOSS_LEFT_DASH,		    BOSS_RIGHT_DASH,          // �뽬 ����
	BOSS_LEFT_HIT1,         BOSS_RIGHT_HIT1,		  // �¾��� �� 1Ÿ
	BOSS_LEFT_HIT2,         BOSS_RIGHT_HIT2,		  // �¾��� �� 2Ÿ
	BOSS_LEFT_HIT3,         BOSS_RIGHT_HIT3,		  // �¾��� �� 3Ÿ
	BOSS_LEFT_HIT_GETUP,    BOSS_RIGHT_HIT_GETUP,	  // �¾��� �� �Ͼ�� ����
	BOSS_LEFT_ATTACK,       BOSS_RIGHT_ATTACK,		  // �� ����
	BOSS_LEFT_ATTACK_ELBOW, BOSS_RIGHT_ATTACK_ELBOW,  // ������ ����
	BOSS_LEFT_JUMP,         BOSS_RIGHT_JUMP,          // ����
	BOSS_LEFT_JUMP_ATTACK,  BOSS_RIGHT_JUMP_ATTACK,   // ���� ����
	BOSS_LEFT_HEAVY_ATTACK, BOSS_RIGHT_HEAVY_ATTACK,  // �� ����
	BOSS_LEFT_DEATH,        BOSS_RIGHT_DEATH,		  // �׾��� ��
	BOSS_LEFT_DEATH_LOOP,   BOSS_RIGHT_DEATH_LOOP,	  // �׾��� �� ����
	BOSS_LEFT_ANGRY,        BOSS_RIGHT_ANGRY,         // ȭ��
	BOSS_END,	
};


class boss : public gameNode
{
private:		
	float      _x, _y, _z;                                 // ���� �߽���
	float      _jumpPower, _gravity;                       // ���� ���� ���� ����		
	float      _angle;                                     // ������ �̵� ����
	float      _applySpeed;                                // ���� ���ǵ�
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
	int        _hitDelay,  _hitCount;                      // �¾��� �� ������, ��� �¾Ҵ��� ī��Ʈ
	// ----------------- ���� ���� ���� -----------------//
	int        _hp, maxHp;
	int        _damage;
	// ----------------- ���� ���� ���� -----------------//

	// ================= �ӽ� ���� �����ϼ��� ================= //
	RECT       _player;
	float      _playerX, _playerY;
	// ================= �ӽ� ���� �����ϼ��� ================= //
	
public:
	boss() {}
	~boss() {}
public:
	HRESULT init();
	void    release();
	void    render();
	void    update();
public:
	void    loadImage();                // ���� �̹��� ���ҽ� �ε�
	void    loadAnimation();            // ���� �ִϸ��̼� �ε�
	void    stateUpdate();              // ���� ������Ʈ ������Ʈ.
public:
	void    attack(float playerX, float playerZ);                   // �÷��̾ ã�Ƽ� �� ����
	void    heavyAttack(float playerX, float playerZ);              // �÷��̾ ã�Ƽ� �� ����
	void    dashAttack(float playerX, float playerZ);               // �뽬 ����
	void    jumpAttack(float playerX, float playerZ);               // ���� ����
	void    elbowAttack(float playerX, float playerZ);              // ���������
	void    changePattern();
};

