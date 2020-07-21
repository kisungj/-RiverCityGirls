#pragma once
#include "gameNode.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")


enum STATEBOSS
{
	BOSS_LEFT_IDLE,         BOSS_RIGHT_IDLE,         // �⺻ ����
	BOSS_LEFT_WALK,         BOSS_RIGHT_WALK,         // �ȴ� ����
	BOSS_LEFT_DASH,		    BOSS_RIGHT_DASH,         // �뽬 ����
	BOSS_LEFT_HIT,          BOSS_RIGHT_HIT,			 // �¾��� ��
	BOSS_LEFT_ATTACK,       BOSS_RIGHT_ATTACK,		 // �� ����
	BOSS_LEFT_ATTACK_ELBOW, BOSS_RIGHT_ATTACK_ELBOW, // ������ ����
	BOSS_LEFT_JUMP_ATTACK,  BOSS_RIGHT_JUMP_ATTACK,  // ���� ����
	BOSS_LEFT_HEAVY_ATTACK, BOSS_RIGHT_HEAVY_ATTACK, // �� ����
	BOSS_LEFT_DEATH,        BOSS_RIGHT_DEATH,		 // �׾��� ��
	BOSS_LEFT_ANGRY,        BOSS_RIGHT_ANGRY,        // ȭ��
	BOSS_END,	
};


class boss : public gameNode
{
private:		
	float      _x, _y, _z;                          // ���� �߽���
	float      _jumpPower, _gravity;                // ���� ���� ���� ����		
	float      _angle;                              // ������ �̵� ����
	float      _applySpeed;                         // ���� ���ǵ�
	STATEBOSS  _state;                              // ���� ���� �����
	RECT       _rc;                                 // ���� �浹 ��Ʈ
	image*     _characterImg;                       // ���� �̹���
	image*     _shadowImg;			                // ���� �׸��� �̹���
	animation* _anim[BOSS_END];                     // �ִϸ��̼� �����
	animation* _animPlayer;                         // �ִϸ��̼� �÷��̿�


	// ================= �ӽ� ���� ���� ================= //
	RECT       _player;
	float      _playerX, _playerY;
	// ================= �ӽ� ���� ���� ================= //
	
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
	void    think();                    // ���� AI �Լ�
	void    stateUpdate();             
};

