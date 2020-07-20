#pragma once
#include "gameNode.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

class playerState;
class idleState;
class moveState;
class jumpState;
class attackState;
class hitState;



class player : public gameNode
{
private:
	playerState* _state;
	image* _img;					//�÷��̾� �̹���
	RECT _rc;						//�÷��̾� �׸��� �̹��� 
	RECT _player;					//�÷��̾�

	int _probeBottom;				//�ȼ��浹�Ұ�
	bool _isMove;					//������ �� �ִ�
	bool _isJumping;				//�����ϴ���
	bool _isUp;						//���Ʒ�

	float _shadowX, _shadowY;		//�׸��� ����
	float _playerX, _playerY;		//�÷��̾� ����

	bool _direction;				//left = 0, right = 1

	float _jumpPower, _gravity;		//�÷��̾� �����Ŀ�, �߷�



	animation* _playerMotion;


	playerState* _idle;
	playerState* _move;
	playerState* _jump;
	playerState* _attack;
	playerState* _hit;


public:
	player() {}
	~player() {}
public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();
public:

	void setState(playerState* state)
	{
		this->_state = state;
	}

public:
	//=====================GET================================
	float getShadowX() { return _shadowX; }
	float getShadowY() { return _shadowY; }
	float getPlayerX() { return _playerX; }
	float getPlayerY() { return _playerY; }
	float getJumpPower() { return _jumpPower; }
	float getGravity() { return _gravity; }
	bool getDirection() { return _direction; }
	bool getIsMove() { return _isMove; }
	bool getIsJumping() { return _isJumping; }
	bool getIsUp() { return _isUp; }
	image* getImgge() { return _img; }



	playerState* getIdleState() { return _idle; }
	playerState* getMoveState() { return _move; }
	playerState* getJumpState() { return _jump; }
	playerState* getAttackState() { return _attack; }
	playerState* getHitState() { return _hit; }

	//=====================SET================================
	void setShadowX(float x) { _shadowX = x; }
	void setShadowY(float y) { _shadowY = y; }
	void setPlayerX(float playerX) { _playerX = playerX; }
	void setPlayerY(float playerY) { _playerY = playerY; }
	void setAni(animation* ani, image* img) { _img = img;  _playerMotion = ani; _playerMotion->start(); }
	void setDirection(bool direction) { _direction = direction; }
	void setJumpPower(float jumpPower) { _jumpPower = jumpPower; }
	void setGravity(float gravity) { _gravity = gravity; }
	void setIsJumping(bool jumping) { _isJumping = jumping; }
	void setIsMove(bool isMove) { _isMove = isMove; }
	void setIsUp(bool isUp) { _isUp = isUp; }
};


class playerState
{
public:
	virtual ~playerState() {}
	virtual void update(player& player) {}
public:
	static idleState* idle;
	static moveState* move;
	static jumpState* jump;
	static attackState* attack;
	static hitState* hit;
};

class idleState : public playerState
{
public:
	virtual void update(player& player) override;
};

class moveState : public playerState
{
public:
	virtual void update(player& player) override;
};

class jumpState : public playerState
{
public:
	virtual void update(player& player) override;
};

class attackState : public playerState
{
public:
	virtual void update(player& player) override;
};

class hitState : public playerState
{
public:
	virtual void update(player& player) override;
};