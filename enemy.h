#pragma once
#include "gameNode.h"
#include "enemyState.h"

enum class CONDITION							//���ʹ� ����(����)
{
	SEARCH,			//�÷��̾�� �� ��
	CLOSE,			//�÷��̾�� ����� ��
	DEAD			//�ֱ�
};

enum class PIXEL								//�̵� �����
{
	LEFT, RIGHT, TOP, BOTTOM, TEMP
};

enum class GREEN								//å�� �ٴ� Ȯ�ο� (����)
{
	LEFT, RIGHT, TOP, BOTTOM, TEMP
};


enum class TABLE								//å�� ���� ����� �� Ȯ�ο�
{
	BOTTOM, TEMP
};

class enemy : public gameNode
{
protected:
	enemyState* _state;				//���� Ŭ���� ����
	CONDITION _condition;			//����
	ENEMYTYPE _et;					//���ʹ� Ÿ��
	PIXEL _pixel;					//�ȼ� �浹��
	GREEN _green;					//������
	TABLE _table;					//å�� ��

	string _mapName;				//�ȼ��浹 �� �ٲٴ¿�

	RECT _rc;						//���ʹ� ��Ʈ
	RECT _shadow;					//���ʹ� �׸��� ��Ʈ
	RECT _attackRC;					//���ʹ� ���� ��Ʈ

	image* _image;					//���ʹ� �̹���
	image* _shadowImg;				//������ �̹���
	int _currentX, _currentY;		//������ x�� , y��
	int _frameCount;				//������ ������ �뵵

	float _x, _y, _z;				//���ʹ� x, y, z��
	float _width, _height;			//���ʹ� �ʺ�, ����
	float _jumpPower, _gravity;		//���ʹ� �����Ŀ�, �׷���Ƽ

	bool _right;					//������ ���ϴ���
	bool _isHit;					//�°� �ִ���
	bool _isStop;					//������ ������
	bool _isLay;					//��������
	bool _isJumping;					//�����ϰ� �ִ���
	bool _isStrike;					//�¾Ҵ���

	int _hitCount;					//���� Ƚ��
	int _layCount;					//���� �ð�
	int _maxHP;						//�ִ� HP

	float _playerX, _playerY;		//�÷��̾� x, y��
	RECT _playerRC;					//�÷��̾� ��Ʈ
	RECT _playerAttack;				//�÷��̾� ���ݷ�Ʈ

	enemyState* _idle;
	enemyState*	_move;
	enemyState* _run;
	enemyState* _jump;
	enemyState*	_attack;
	enemyState* _hit;
	enemyState* _down;
	enemyState* _beg;
	enemyState* _dizzy;
	enemyState* _dead;

public:
	enemy();
	~enemy();

	virtual HRESULT init(float x, float y, ENEMYTYPE et, string mapName);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void directionCheck(RECT rc, float x, float y);
	void draw();												//������ ������ �뵵
	void pixelCollision();										//�ȼ� �浹
	void addImage();											//�̹����Ŵ��� �Ѱ��� ��Ƶα�


public:
	RECT getRC() { return _rc; }								//���ʹ� ��Ʈ ��������
	RECT getShadow() { return _shadow; }						//�׸��� ��Ʈ ��������
	RECT getAtk() { return _attackRC; }							//���� ��Ʈ ��������
	image* getImage() { return _image; }						//�̹��� ��������
	CONDITION getCondition() { return _condition; }				//CONDITION ��������
	PIXEL getPixel() { return _pixel; }							//PIXEL ��������
	GREEN getGreen() { return _green; }							//GREEN ��������
	TABLE getTable() { return _table; }							//TABLE ��������

	float getX() { return _x; }									//x�� ��������
	float getY() { return _y; }									//y�� ��������
	float getZ() { return _z; }									//z�� ��������

	bool getRight() { return _right; }							//_right ��������
	bool getStop() { return _isStop; }							//_isStop ��������
	bool getOuch() { return _isHit; }							//_isHit ��������
	bool getLay() { return _isLay; }							//_isLay ��������
	bool getJumping() { return _isJumping; }					//_isJump ��������
	bool getStrike() { return _isStrike; }						//_isStrike ��������

	int getHitCount() { return _hitCount; }						//_hitCount ��������
	int getLayCount() { return _layCount; }						//_layCount ��������
	int getHP() { return _maxHP; }								//_maxHP ��������

	int getFrameX() { return _currentX; }						//������X ��������
	int getFrameY() { return _currentY; }						//������Y ��������

	float getJumpPower() { return _jumpPower; }					//�����Ŀ� ��������
	float getGravity() { return _gravity; }						//�׶��Ƽ ��������
	

public:
	void setRC(float x, float y, float width, float height)		//���ʹ� ��Ʈ �������ֱ�
	{
		_rc = RectMakeCenter(x, y, width, height);
	}

	void setAtk(float x, float y, float width, float height)	//���ʹ� ���� ��Ʈ �������ֱ�
	{
		_attackRC = RectMakeCenter(x, y, width, height);
	}

	void setState(enemyState* state) { this->_state = state; }	//���� Ŭ���� �������ֱ�
	void setImage(image* image) { this->_image = image; }		//�̹��� �������ֱ�
	void setCond(CONDITION cond) { this->_condition = cond; }	//����� �����ֱ�

	void setX(float x) { _x = x; }								//x�� �����̰� �ϱ�
	void setY(float y) { _y = y; }								//y�� �����̰� �ϱ�
	void setZ(float z) { _z = z; }								//z�� �����̰� �ϱ�

	void setStop(BOOL stop = FALSE) { _isStop = stop; }			//_isStop �������ֱ�
	void setOuch(BOOL hit = FALSE) { _isHit = hit; }			//_isHit �������ֱ�			//�÷��̾����� ���� �� �ʿ�
	void setLay(BOOL lay = FALSE) { _isLay = lay; }				//_isLay �������ֱ�
	void setJumping(BOOL jump = FALSE) { _isJumping = jump; }			//_isJump �������ֱ�
	void setStrike(BOOL st = FALSE) { _isStrike = st; }			//_isStrike �������ֱ�

	void setHitCount(int count) { _hitCount += count; }			//_hitCount �÷��ֱ�			//�÷��̾����� ���� ��(����� 1, ������ 3 �̻�)
	void setLayCount(int count) { _layCount += count; }			//_layCount �÷��ֱ�
	void setHP(int hp) { _maxHP -= hp; }						//_maxHP ���				//�÷��̾����� ���� �� �ʿ�

	void setFrameX(int x) { _currentX = x; }					//������X �������ֱ�
	void setFrameY(int y) { _currentY = y; }					//������y �������ֱ�

	void setJumpPower(float power) { _jumpPower = power; }		//�����Ŀ� �����ֱ�
	void setGravity(float g) { _gravity = g; }					//�׷���Ƽ �����ֱ�


public:
	enemyState* getIdle() { return _idle; }						//���� Ŭ���� ������ �� �ʿ�
	enemyState* getMove() { return _move; }
	enemyState* getRun() { return _run; }
	enemyState* getJump() { return _jump; }
	enemyState* getAttack() { return _attack; }
	enemyState* getHit() { return _hit; }
	enemyState* getDown() { return _down; }
	enemyState* getDizzy() { return _dizzy; }
	enemyState* getDie() { return _dead; }
};