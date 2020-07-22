#pragma once
#include "gameNode.h"

enum OBSTACLESTATE
{
	VENDING,
	DESK,
	PILLARLEFT,
	PILLARRIGHT
};


class obstacle : public gameNode
{
private:
	image* _obstacleImg;				//��ֹ� �̹���
	RECT _obstacleRc;					//���Ǳ� ��Ʈ
	RECT _PillarRc;						//��� ��Ʈ
	OBSTACLESTATE  _obstacleState;		//��ֹ� enum��

	float _x, _y;						//��ֹ� ��ġ��
	bool _alpha;						//��� ���� ó��

public:
	obstacle();
	~obstacle();

	virtual HRESULT init(OBSTACLESTATE obstacleState, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	RECT getObsRc() { return _obstacleRc; }						//���Ǳ� ��Ʈ�� �Ѱ���
	RECT getPillarRc() { return _PillarRc; }					//��� ��Ʈ�� �Ѱ���
	OBSTACLESTATE getObstacleState() { return _obstacleState; }	//��ֹ� enum�� �Ѱ���
	void setAlphaValue(bool bol = TRUE) { _alpha = bol; }		//��� ���İ� ����

	void collision();											//��հ� �浹������
};

