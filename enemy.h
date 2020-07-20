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
	//HITSTATE _hitState;			//���� ����

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
	bool _isLay;					//��������

	int _hitCount;					//���� Ƚ��
	int _layCount;					//���� �ð�

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


public:
	RECT getRC() { return _rc; }								//���ʹ� ��Ʈ ��������
	RECT getShadow() { return _shadow; }						//�׸��� ��������
	image* getImage() { return _image; }						//�̹��� ��������
	CONDITION getCondition() { return _condition; }				//CONDITION ��������

	float getX() { return _x; }									//x�� ��������
	float getY() { return _y; }									//y�� ��������

	bool getRight() { return _right; }							//_right ��������
	bool getStop() { return _isStop; }							//_isStop ��������
	bool getOuch() { return _isHit; }							//_isHit ��������
	bool getLay() { return _isLay; }							//_isLay ��������

	int getHitCount() { return _hitCount; }						//_hitCount ��������
	int getLayCount() { return _layCount; }						//_layCount ��������
	int getFrameX() { return _currentX; }						//������X ��������
	int getFrameY() { return _currentY; }						//������Y ��������
	

public:
	void setRC(float x, float y, float width, float height)		//���ʹ� ��Ʈ �������ֱ�
	{
		_rc = RectMakeCenter(x, y, width, height);
	}

	void setState(enemyState* state) { this->_state = state; }	//���� Ŭ���� �������ֱ�
	void setImage(image* image) { this->_image = image; }		//�̹��� �������ֱ�

	void setX(float x) { _x = x; }								//x�� �����̰� �ϱ�
	void setY(float y) { _y = y; }								//y�� �����̰� �ϱ�

	void setStop(BOOL stop = FALSE) { _isStop = stop; }			//_isStop �������ֱ�
	void setOuch(BOOL hit = FALSE) { _isHit = hit; }			//_isHit �������ֱ�
	void setLay(BOOL lay = FALSE) { _isLay = lay; }				//_isLay �������ֱ�

	void setHitCount(int count) { _hitCount += count; }			//_hitCount �÷��ֱ�
	void setLayCount(int count) { _layCount += count; }			//_layCount �÷��ֱ�
	void setFrameX(int x) { _currentX = x; }					//������X �������ֱ�
	void setFrameY(int y) { _currentY = y; }					//������y �������ֱ�

	void setJump(float power) { _jumpPower = power; }			//�����Ŀ� �����ֱ�
	void setGravity(float g) { _gravity = g; }					//�׷���Ƽ �����ֱ�


	enemyState* getMove() { return _move; }						//���� Ŭ���� ������ �� �ʿ�
	enemyState* getAttack() { return _attack; }
	enemyState* getGuard() { return _guard; }
	enemyState* getHit() { return _hit; }
	enemyState* getDown() { return _down; }
	enemyState* getBeg() { return _beg; }
	enemyState* getDizzy() { return _dizzy; }
};