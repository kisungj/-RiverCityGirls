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

	float _x, _y, _z;					//��ֹ� ��ġ��
	int	_pillarAlpha;					//��� ���� ��ġ
	bool _alpha;						//��� ���� ó��
	bool _deskZOrder;					//����ũ ZOrder ó��

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
	bool getDeskZOrder() { return _deskZOrder; }				//å�� Z-Order
	void setDeskZOrder(bool desk) { _deskZOrder = desk; }
	void collision();											//��հ� �浹������
};

