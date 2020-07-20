#pragma once
#include "gameNode.h"
#include "enemyState.h"

enum class CONDITION
{
	SEARCH,
	CLOSE
};

enum class HITSTATE
{
	HIT1, HIT2, HIT3
};

class enemy : public gameNode
{
private:
	enemyState* _state;				//���� Ŭ���� ����
	CONDITION _condition;			//����
	//HITSTATE _hitState;				//���� ����

	RECT _rc;						//���ʹ� ��Ʈ
	RECT _shadow;					//���ʹ� �׸��� ��Ʈ

	image* _image;					//���ʹ� �̹���
	int _currentX, _currentY;		//������ x�� , y��
	int _frameCount;				//������ ������ �뵵

	float _x, _y;					//���ʹ� x, y��
	float _width, _height;			//���ʹ� �ʺ�, ����
	float _jumpPower, _gravity;		//���ʹ� �����Ŀ�, �׷���Ƽ

	bool _right;					//������ ���ϴ���
	bool _isHit;					//�°� �ִ���
	bool _isStop;					//������ ������

	int _hitCount;					//���� Ƚ��

	float _playerX, _playerY;		//�÷��̾� x, y��
	RECT _playerRC;					//�÷��̾� ��Ʈ
	RECT _playerAttack;				//�÷��̾� ���ݷ�Ʈ

	enemyState*	_move;
	enemyState*	_attack;
	enemyState* _guard;
	enemyState* _hit;
	enemyState* _down;
	enemyState* _beg;
	enemyState* _dizzy;

	bool _test;

public:
	enemy();
	~enemy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void directionCheck(RECT rc, float x, float y);
	void draw();												//������ ������ �뵵

	void addImage();											//�̹����Ŵ��� �Ѱ��� ��Ƶα�

	float getX() { return _x; }									//x�� ��������
	void setX(float x) { _x = x; }								//x�� �����̰� �ϱ�
	float getY() { return _y; }									//y�� ��������
	void setY(float y) { _y = y; }								//y�� �����̰� �ϱ�

	RECT getShadow() { return _shadow; }						//�׸��� ��������
	void setJump(float power) { _jumpPower = power; }			//�����Ŀ� �����ֱ�
	void setGravity(float g) { _gravity = g; }					//�׷���Ƽ �����ֱ�

	RECT getRC() { return _rc; }								//���ʹ� ��Ʈ ��������
	void setRC(float x, float y, float width, float height)		//���ʹ� ��Ʈ �������ֱ�
	{
		_rc = RectMakeCenter(x, y, width, height);
	}

	bool getRight() { return _right; }							//_right ��������
	CONDITION getCondition() { return _condition; }				//CONDITION ��������
	bool getStop() { return _isStop; }							//_isStop ��������
	void setStop(BOOL stop = FALSE) { _isStop = stop; }			//_isStop �������ֱ�

	bool getOuch() { return _isHit; }							//_isHit ��������
	void setOuch(BOOL hit = FALSE) { _isHit = hit; }			//_isHit �������ֱ�
	int getHitCount() { return _hitCount; }						//_hitCount ��������
	void setHitCount(int count) { _hitCount += count; }			//_hitCount �÷��ֱ�

	void setState(enemyState* state) { this->_state = state; }	//���� Ŭ���� �������ֱ�
	image* getImage() { return _image; }						//�̹��� ��������
	void setImage(image* image) { this->_image = image; }		//�̹��� �������ֱ�
	int getFrameX() { return _currentX; }						//������ ��������
	void setFrameX(int x) { _currentX = x; }					//������ �������ֱ�






	enemyState* getMove() { return _move; }						//���� Ŭ���� ������ �� �ʿ�
	enemyState* getAttack() { return _attack; }
	enemyState* getGuard() { return _guard; }
	enemyState* getHit() { return _hit; }
	enemyState* getDown() { return _down; }
	enemyState* getBeg() { return _beg; }
	enemyState* getDizzy() { return _dizzy; }
};