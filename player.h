#pragma once
#include "gameNode.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

class playerState;
class idleState;
class walkState;
class runState;
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

	int _probeV;					//�ȼ��浹 ����
	int _probeH;					//�ȼ��浹 ����
	bool _isBottom;					//�Ʒ�
	bool _isTop;					//��
	bool _isLeft;					//����
	bool _isRight;					//������
	bool _isJumping;				//�����ϴ���


	float _shadowX, _shadowY;		//�׸��� ����
	float _playerX, _playerY;		//�÷��̾� ����

	bool _directionX;				//left = 0, right = 1
	bool _directionY;				//top = 0, bottom = 1

	float _jumpPower, _gravity;		//�÷��̾� �����Ŀ�, �߷�

	int _runCount;					//������ �޸���


	animation* _playerMotion;


	playerState* _idle;
	playerState* _walk;
	playerState* _run;
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

	void keyAnimation();

public:
	//=====================GET================================
	float getShadowX() { return _shadowX; }
	float getShadowY() { return _shadowY; }
	float getPlayerX() { return _playerX; }
	float getPlayerY() { return _playerY; }
	float getJumpPower() { return _jumpPower; }
	float getGravity() { return _gravity; }
	int getRunCount() { return _runCount; }
	bool getDirectionX() { return _directionX; }
	bool getDirectionY() { return _directionY; }
	bool getIsBottom() { return _isBottom; }
	bool getIsTop() { return _isTop; }
	bool getIsRight() { return _isRight; }
	bool getIsLeft() { return _isLeft; }
	bool getIsJumping() { return _isJumping; }
	image* getImgge() { return _img; }



	playerState* getIdleState() { return _idle; }
	playerState* getWalkState() { return _walk; }
	playerState* getRunState() { return _run; }
	playerState* getJumpState() { return _jump; }
	playerState* getAttackState() { return _attack; }
	playerState* getHitState() { return _hit; }

	//=====================SET================================
	void setShadowX(float x) { _shadowX = x; }
	void setShadowY(float y) { _shadowY = y; }
	void setPlayerX(float playerX) { _playerX = playerX; }
	void setPlayerY(float playerY) { _playerY = playerY; }
	void setAni(animation* ani, image* img) { _img = img;  _playerMotion = ani; _playerMotion->start(); }
	void setDirectionX(bool direction) { _directionX = direction; }
	void setDirectionY(bool direction) { _directionY = direction; }
	void setJumpPower(float jumpPower) { _jumpPower = jumpPower; }
	void setGravity(float gravity) { _gravity = gravity; }
	void setRunCount(int runCount) { _runCount = runCount; }
	void setIsJumping(bool jumping) { _isJumping = jumping; }
	void setIsBottom(bool isMove) { _isBottom = isMove; }
	void setIsTop(bool isMove) { _isTop = isMove; }
	void setIsRight(bool isMove) { _isRight = isMove; }
	void setIsLeft(bool isMove) { _isLeft = isMove; }
};


class playerState
{
public:
	virtual ~playerState() {}
	virtual void update(player& player) {}
public:
	static idleState* idle;
	static walkState* walk;
	static runState* run;
	static jumpState* jump;
	static attackState* attack;
	static hitState* hit;
};

class idleState : public playerState
{
public:
	virtual void update(player& player) override;
};

class walkState : public playerState
{
public:
	virtual void update(player& player) override;
};

class runState : public playerState
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