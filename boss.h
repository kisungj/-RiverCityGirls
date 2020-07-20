#pragma once
#include "gameNode.h"

enum STATEBOSS
{
	BOSS_LEFT_IDLE,         BOSS_RIGHT_IDLE,         // �⺻ ����
	BOSS_LEFT_WALK,         BOSS_RIGHT_WALK,         // �ȴ� ����
	BOSS_LEFT_HIT,          BOSS_RIGHT_HIT,			 // �¾��� ��
	BOSS_LEFT_HIT_GETUP,    BOSS_RIGHT_HIT_GETUP,	 // �°� �ٽ� �Ͼ�鼭 ����
	BOSS_LEFT_HIT_GROUND,   BOSS_RIGHT_HIT_GROUND,   // ������ �÷��̾����� �¾��� ��
	BOSS_LEFT_ATTACK,       BOSS_RIGHT_ATTACK,		 // �� ����
	BOSS_LEFT_HEAVY_ATTACK, BOSS_RIGHT_HEAVY_ATTACK, // �� ����
	BOSS_LEFT_ATTACK_ELBOW, BOSS_RIGHT_ATTACK_ELBOW, // ������ ����
	BOSS_LEFT_DEATH,        BOSS_RIGHT_DEATH,		 // �׾��� ��
	BOSS_LEFT_BLOCK,        BOSS_RIGHT_BLOCK,		 // ������ ��
	BOSS_END,	
};


class boss : public gameNode
{
private:		
	float      _x, _y;                 // ���� �߽���
	float      _jumpPower, _gravity;   // ���� ���� ���� ����		
	STATEBOSS  _state;                 // ���� ���� �����
	RECT       _rc;                    // ���� �浹 ��Ʈ
	image*     _img;                   // ���� �̹���

	animation* _anim[BOSS_END];
	animation* _animPlay;
	// ============ �ӽ� ���� ============ //
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

