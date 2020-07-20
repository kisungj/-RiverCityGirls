#pragma once
class iEvent
{
public:
	//이벤트 시작할때 실행할 함수
	virtual void eventStart() = 0;
	//이벤트 업데이트
	virtual bool eventUpdate() = 0;
};


class iCameraMove : public iEvent
{
	// 이동시킬 좌표
	POINTFLOAT mTargetLocation;
	// 스피드
	float mSpeed;

public:
	iCameraMove(POINTFLOAT targetLocation, float speed);
	void eventStart()override;
	bool eventUpdate()override;
};

class iWaitForSecond : public iEvent
{
	float _timer;
	float _maxTimer;

public:
	iWaitForSecond(float timer);
	void eventStart()override;
	bool eventUpdate()override;
};
