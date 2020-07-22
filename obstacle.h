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
	image* _obstacleImg;				//장애물 이미지
	RECT _obstacleRc;					//자판기 렉트
	RECT _PillarRc;						//기둥 렉트
	OBSTACLESTATE  _obstacleState;		//장애물 enum값

	float _x, _y;						//장애물 위치값
	bool _alpha;						//기둥 알파 처리

public:
	obstacle();
	~obstacle();

	virtual HRESULT init(OBSTACLESTATE obstacleState, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	RECT getObsRc() { return _obstacleRc; }						//자판기 렉트값 넘겨줌
	RECT getPillarRc() { return _PillarRc; }					//기둥 렉트값 넘겨줌
	OBSTACLESTATE getObstacleState() { return _obstacleState; }	//장애물 enum값 넘겨줌
	void setAlphaValue(bool bol = TRUE) { _alpha = bol; }		//기둥 알파값 설정

	void collision();											//기둥과 충돌했을때
};

