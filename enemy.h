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
	enemyState* _state;				//현재 클래스 상태
	CONDITION _condition;			//상태
	//HITSTATE _hitState;				//맞은 상태

	RECT _rc;						//에너미 렉트
	RECT _shadow;					//에너미 그림자 렉트

	image* _image;					//에너미 이미지
	int _currentX, _currentY;		//프레임 x축 , y축
	int _frameCount;				//프레임 돌리는 용도

	float _x, _y;					//에너미 x, y축
	float _width, _height;			//에너미 너비, 높이
	float _jumpPower, _gravity;		//에너미 점프파워, 그래비티

	bool _right;					//오른쪽 향하는지
	bool _isHit;					//맞고 있는지
	bool _isStop;					//프레임 조절용

	int _hitCount;					//맞은 횟수

	float _playerX, _playerY;		//플레이어 x, y축
	RECT _playerRC;					//플레이어 렉트
	RECT _playerAttack;				//플레이어 공격렉트

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
	void draw();												//프레임 돌리는 용도

	void addImage();											//이미지매니저 한곳에 모아두기

	float getX() { return _x; }									//x축 가져가기
	void setX(float x) { _x = x; }								//x축 움직이게 하기
	float getY() { return _y; }									//y축 가져가기
	void setY(float y) { _y = y; }								//y축 움직이게 하기

	RECT getShadow() { return _shadow; }						//그림자 가져가기
	void setJump(float power) { _jumpPower = power; }			//점프파워 정해주기
	void setGravity(float g) { _gravity = g; }					//그래비티 정해주기

	RECT getRC() { return _rc; }								//에너미 렉트 가져가기
	void setRC(float x, float y, float width, float height)		//에너미 렉트 설정해주기
	{
		_rc = RectMakeCenter(x, y, width, height);
	}

	bool getRight() { return _right; }							//_right 가져가기
	CONDITION getCondition() { return _condition; }				//CONDITION 가져가기
	bool getStop() { return _isStop; }							//_isStop 가져가기
	void setStop(BOOL stop = FALSE) { _isStop = stop; }			//_isStop 세팅해주기

	bool getOuch() { return _isHit; }							//_isHit 가져가기
	void setOuch(BOOL hit = FALSE) { _isHit = hit; }			//_isHit 세팅해주기
	int getHitCount() { return _hitCount; }						//_hitCount 가져가기
	void setHitCount(int count) { _hitCount += count; }			//_hitCount 올려주기

	void setState(enemyState* state) { this->_state = state; }	//상태 클래스 변경해주기
	image* getImage() { return _image; }						//이미지 가져가기
	void setImage(image* image) { this->_image = image; }		//이미지 변경해주기
	int getFrameX() { return _currentX; }						//프레임 가져가기
	void setFrameX(int x) { _currentX = x; }					//프레임 변경해주기






	enemyState* getMove() { return _move; }						//상태 클래스 변경할 때 필요
	enemyState* getAttack() { return _attack; }
	enemyState* getGuard() { return _guard; }
	enemyState* getHit() { return _hit; }
	enemyState* getDown() { return _down; }
	enemyState* getBeg() { return _beg; }
	enemyState* getDizzy() { return _dizzy; }
};