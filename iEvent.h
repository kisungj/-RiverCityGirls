#pragma once
class iEvent
{
public:
	//�̺�Ʈ �����Ҷ� ������ �Լ�
	virtual void eventStart() = 0;
	//�̺�Ʈ ������Ʈ
	virtual bool eventUpdate() = 0;
};


class iCameraMove : public iEvent
{
	// �̵���ų ��ǥ
	POINTFLOAT mTargetLocation;
	// ���ǵ�
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
