#pragma once
#include "gameNode.h"
#include "enemyState.h"

enum class CONDITION							//에너미 상태(간단)
{
	SEARCH,			//플레이어와 멀 때
	CLOSE,			//플레이어와 가까울 때
	DEAD			//주금
};

enum class PIXEL								//이동 막기용
{
	LEFT, RIGHT, TOP, BOTTOM, TEMP
};

enum class GREEN								//책상 바닥 확인용 (점프)
{
	LEFT, RIGHT, TOP, BOTTOM, TEMP
};


enum class TABLE								//책상 위에 닿았을 때 확인용
{
	BOTTOM, TEMP
};

class enemy : public gameNode
{
protected:
	enemyState* _state;				//현재 클래스 상태
	CONDITION _condition;			//상태
	ENEMYTYPE _et;					//에너미 타입
	PIXEL _pixel;					//픽셀 충돌용
	GREEN _green;					//점프용
	TABLE _table;					//책상 위

	string _mapName;				//픽셀충돌 맵 바꾸는용

	RECT _rc;						//에너미 렉트
	RECT _shadow;					//에너미 그림자 렉트
	RECT _attackRC;					//에너미 공격 렉트

	image* _image;					//에너미 이미지
	image* _shadowImg;				//쉐도우 이미지
	int _currentX, _currentY;		//프레임 x축 , y축
	int _frameCount;				//프레임 돌리는 용도

	float _x, _y, _z;				//에너미 x, y, z축
	float _width, _height;			//에너미 너비, 높이
	float _jumpPower, _gravity;		//에너미 점프파워, 그래비티

	bool _right;					//오른쪽 향하는지
	bool _isHit;					//맞고 있는지
	bool _isStop;					//프레임 조절용
	bool _isLay;					//누웠는지
	bool _isJumping;					//점프하고 있는지
	bool _isStrike;					//맞았는지

	int _hitCount;					//맞은 횟수
	int _layCount;					//누운 시간
	int _maxHP;						//최대 HP

	float _playerX, _playerY;		//플레이어 x, y축
	RECT _playerRC;					//플레이어 렉트
	RECT _playerAttack;				//플레이어 공격렉트

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
	void draw();												//프레임 돌리는 용도
	void pixelCollision();										//픽셀 충돌
	void addImage();											//이미지매니저 한곳에 모아두기


public:
	RECT getRC() { return _rc; }								//에너미 렉트 가져가기
	RECT getShadow() { return _shadow; }						//그림자 렉트 가져가기
	RECT getAtk() { return _attackRC; }							//공격 렉트 가져가기
	image* getImage() { return _image; }						//이미지 가져가기
	CONDITION getCondition() { return _condition; }				//CONDITION 가져가기
	PIXEL getPixel() { return _pixel; }							//PIXEL 가져가기
	GREEN getGreen() { return _green; }							//GREEN 가져가기
	TABLE getTable() { return _table; }							//TABLE 가져가기

	float getX() { return _x; }									//x축 가져가기
	float getY() { return _y; }									//y축 가져가기
	float getZ() { return _z; }									//z축 가져가기

	bool getRight() { return _right; }							//_right 가져가기
	bool getStop() { return _isStop; }							//_isStop 가져가기
	bool getOuch() { return _isHit; }							//_isHit 가져가기
	bool getLay() { return _isLay; }							//_isLay 가져가기
	bool getJumping() { return _isJumping; }					//_isJump 가져가기
	bool getStrike() { return _isStrike; }						//_isStrike 가져가기

	int getHitCount() { return _hitCount; }						//_hitCount 가져가기
	int getLayCount() { return _layCount; }						//_layCount 가져가기
	int getHP() { return _maxHP; }								//_maxHP 가져가기

	int getFrameX() { return _currentX; }						//프레임X 가져가기
	int getFrameY() { return _currentY; }						//프레임Y 가져가기

	float getJumpPower() { return _jumpPower; }					//점프파워 가져가기
	float getGravity() { return _gravity; }						//그라비티 가져가기
	

public:
	void setRC(float x, float y, float width, float height)		//에너미 렉트 설정해주기
	{
		_rc = RectMakeCenter(x, y, width, height);
	}

	void setAtk(float x, float y, float width, float height)	//에너미 공격 렉트 설정해주기
	{
		_attackRC = RectMakeCenter(x, y, width, height);
	}

	void setState(enemyState* state) { this->_state = state; }	//상태 클래스 변경해주기
	void setImage(image* image) { this->_image = image; }		//이미지 변경해주기
	void setCond(CONDITION cond) { this->_condition = cond; }	//컨디션 정해주기

	void setX(float x) { _x = x; }								//x축 움직이게 하기
	void setY(float y) { _y = y; }								//y축 움직이게 하기
	void setZ(float z) { _z = z; }								//z축 움직이게 하기

	void setStop(BOOL stop = FALSE) { _isStop = stop; }			//_isStop 세팅해주기
	void setOuch(BOOL hit = FALSE) { _isHit = hit; }			//_isHit 세팅해주기			//플레이어한테 맞을 때 필요
	void setLay(BOOL lay = FALSE) { _isLay = lay; }				//_isLay 세팅해주기
	void setJumping(BOOL jump = FALSE) { _isJumping = jump; }			//_isJump 세팅해주기
	void setStrike(BOOL st = FALSE) { _isStrike = st; }			//_isStrike 세팅해주기

	void setHitCount(int count) { _hitCount += count; }			//_hitCount 올려주기			//플레이어한테 맞을 때(약공격 1, 강공격 3 이상)
	void setLayCount(int count) { _layCount += count; }			//_layCount 올려주기
	void setHP(int hp) { _maxHP -= hp; }						//_maxHP 깎기				//플레이어한테 맞을 때 필요

	void setFrameX(int x) { _currentX = x; }					//프레임X 변경해주기
	void setFrameY(int y) { _currentY = y; }					//프레임y 변경해주기

	void setJumpPower(float power) { _jumpPower = power; }		//점프파워 정해주기
	void setGravity(float g) { _gravity = g; }					//그래비티 정해주기


public:
	enemyState* getIdle() { return _idle; }						//상태 클래스 변경할 때 필요
	enemyState* getMove() { return _move; }
	enemyState* getRun() { return _run; }
	enemyState* getJump() { return _jump; }
	enemyState* getAttack() { return _attack; }
	enemyState* getHit() { return _hit; }
	enemyState* getDown() { return _down; }
	enemyState* getDizzy() { return _dizzy; }
	enemyState* getDie() { return _dead; }
};