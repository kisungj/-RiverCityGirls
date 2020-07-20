#pragma once
#include "gameNode.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

class playerState;
class idleState;
class moveState;
class jumpState;



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

	float _shadowX, _shadowY;		//�׸��� ����
	float _playerX, _playerY;		//�÷��̾� ����

	bool _direction;				//left = 0, right = 1

	float _jumpPower, _gravity;		//�÷��̾� �����Ŀ�, �߷�



	animation* _playerMotion;


	playerState* _idle;
	playerState* _move;
	playerState* _jump;


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



	playerState* getIdleState() { return _idle; }
	playerState* getMoveState() { return _move; }
	playerState* getJumpState() { return _jump; }

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


