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
class downState;		//��
class startState;
class guardState;
class overState;
class stunState;


class player : public gameNode
{
private:
	playerState* _state;
	image* _img;					//�÷��̾� �̹���
	image* _shadowImg;				//������ �̹���
	RECT _shadow;					//�÷��̾� �׸��� �̹��� 
	RECT _player;					//�÷��̾�
	RECT _attackRc;					//���ݷ�Ʈ

	string _mapStr;					//�ȼ��浹 �� �ٲٴ¿�

	int _probeV;					//�ȼ��浹 ����
	int _probeH;					//�ȼ��浹 ����
	int _playerProbe;				//å�� �ö󰡴¿�
	int _runCount;					//������ �޸���
	int _shadowAlpha;				//�׸��� ����

	float _shadowX, _shadowY;		//�׸��� ����
	float _playerX, _playerY;		//�÷��̾� ����
	float _attackX, _attackY;		//������ ����
	float _attackSizeX, _attackSizeY;//���÷�Ʈ�� ������
	float _currentHP, _maxHP;		//ü��
	float _jumpPower, _gravity;		//�÷��̾� �����Ŀ�, �߷�
	float _deskTimer;

	bool _isBottom;					//�Ʒ�
	bool _isTop;					//��
	bool _isLeft;					//����
	bool _isRight;					//������
	bool _isDesk;					//å������ �ö󰬴���
	bool _isJumping;				//�����ϴ���
	bool _isDeskFall;				//����ũ �浹 �׽�Ʈ
	bool _isRun;					//�ٴ���
	bool _isAttack;					//�����Ұ�?
	bool _attacked;					//���� 3�� �̾��ֱ�
	bool _directionX;				//left = 0, right = 1
	bool _directionY;				//top = 0, bottom = 1




	animation* _playerMotion;


	playerState* _idle;
	playerState* _walk;
	playerState* _run;
	playerState* _jump;
	playerState* _attack;
	playerState* _hit;
	playerState* _down;
	playerState* _start;
	playerState* _guard;
	playerState* _over;
	playerState* _stun;


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

	void playerDamage(float damage);

	void mouseCol();
	void pixelCol();
	void boolCheck();

public:
	//=====================GET================================
	float getShadowX() { return _shadowX; }
	float getShadowY() { return _shadowY; }
	float getPlayerX() { return _playerX; }
	float getPlayerY() { return _playerY; }
	float getJumpPower() { return _jumpPower; }
	float getGravity() { return _gravity; }
	float getPlayerHp() { return _currentHP; }
	float getPlayerMaxHP() { return _maxHP; }
	int getRunCount() { return _runCount; }
	int getShadow() { return _shadowAlpha; }
	bool getDirectionX() { return _directionX; }
	bool getDirectionY() { return _directionY; }
	bool getIsBottom() { return _isBottom; }
	bool getIsTop() { return _isTop; }
	bool getIsRight() { return _isRight; }
	bool getIsLeft() { return _isLeft; }
	bool getIsJumping() { return _isJumping; }
	bool getIsRun() { return _isRun; }
	bool getAttacked() { return _attacked; }
	bool getIsAttack() { return _isAttack; }
	bool getIsDeskFall() { return _isDeskFall; }
	RECT getAttackRect() { return _attackRc; }
	RECT getPlayerRect() { return _player; }
	image* getImgge() { return _img; }
	animation* getAni() { return _playerMotion; }



	playerState* getIdleState() { return _idle; }
	playerState* getWalkState() { return _walk; }
	playerState* getRunState() { return _run; }
	playerState* getJumpState() { return _jump; }
	playerState* getAttackState() { return _attack; }
	playerState* getHitState() { return _hit; }
	playerState* getDownState() { return _down; }
	playerState* getStartState() { return _start; }
	playerState* getGuardState() { return _guard; }
	playerState* getOverState() { return _over; }
	playerState* getStunState() { return _stun; }

	//=====================SET================================
	void setShadowX(float x) { _shadowX = x; }
	void setShadowY(float y) { _shadowY = y; }
	void setPlayerX(float playerX) { _playerX = playerX; }
	void setPlayerY(float playerY) { _playerY = playerY; }
	void setJumpPower(float jumpPower) { _jumpPower = jumpPower; }
	void setGravity(float gravity) { _gravity = gravity; }
	void setPlayerHP(float hp) { _currentHP = hp; }
	void setAttack(float attackX, float attackY, float attackSizeX, float attackSizeY)
	{
		_attackX = attackX; _attackY = attackY; _attackSizeX = attackSizeX; _attackSizeY = attackSizeY;
	}
	void setRunCount(int runCount) { _runCount = runCount; }
	void setShadow(int shadow) { _shadowAlpha = shadow; }
	void setDirectionX(bool direction) { _directionX = direction; }
	void setDirectionY(bool direction) { _directionY = direction; }
	void setIsJumping(bool jumping) { _isJumping = jumping; }
	void setIsBottom(bool isMove) { _isBottom = isMove; }
	void setIsTop(bool isMove) { _isTop = isMove; }
	void setIsRight(bool isMove) { _isRight = isMove; }
	void setIsLeft(bool isMove) { _isLeft = isMove; }
	void setIsRun(bool isRun) { _isRun = isRun; }
	void setIsAttack(bool isAttack) { _isAttack = isAttack; }
	void setAttacked(bool attacked) { _attacked = attacked; }
	void setIsDeskFall(bool fall) { _isDeskFall = fall; }
	void setAttackRect(RECT attackRc) { _attackRc = attackRc; }
	void setMapStr(string str) { _mapStr = str; }
	void setAni(animation* ani, image* img) { _img = img;  _playerMotion = ani; _playerMotion->start(); }
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
	static downState* down;
	static startState* gameStart;
	static guardState* guard;
	static overState* over;
	static stunState* stun;
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
private:
	int _jumpCount;		//stayŰ ���Ƽ� ���� �׸� �ö󰡰�
	bool _isJump;		//�̰� ����,. ������..
public:
	HRESULT init();
	virtual void update(player& player) override;
};

class attackState : public playerState
{
private:
	int _diveCount;		//���̺� �ӵ� �ַ���
public:
	HRESULT init();
	virtual void update(player& player) override;
};

class hitState : public playerState
{
private:
	int _hitCount;
	int _stunCount;
	int _hitNum;
	bool _isHit;
public:
	HRESULT init();
	virtual void update(player& player) override;
};

class downState : public playerState
{
private:
	int _downCount;
public:
	HRESULT init();
	virtual void update(player& player) override;
};

class startState : public playerState
{
public:
	virtual void update(player& player) override;
};

class guardState : public playerState
{
public:
	virtual void update(player& player) override;
};

class overState : public playerState
{
public: 
	virtual void update(player& player) override;
};

class stunState : public playerState
{
public:
	virtual void update(player& player) override;
};