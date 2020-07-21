#pragma once
#include "gameNode.h"

enum ITEMSTATE
{
	HP,
	POWER,
	GOLD,
	SILVER
};

class Item : public gameNode
{
private:
	image*		_itemImg;			//아이템 이미지
	ITEMSTATE	_itemState;			//아이템 enum값
	RECT		_itemRc;			//아이템 렉트
	string		_name;				//아이템 이름
	string		_discription;		//아이템 설명

	float _x, _y;					//아이템 위치값
	float _gravity;					//아이템 떨어지는 중력값

	float _hpAmount;				//HP 증가량
	float _attackAmount;			//공격력 증가량

	bool _gravityBool;				//아이템 떨어지는 불값

public:
	Item();
	~Item();

	virtual HRESULT init(ITEMSTATE itemstate, POINT position);
	virtual void update();
	virtual void release();
	virtual void render();

	void move();											//아이템 드랍시 떨어지게

	RECT getItemRc() { return _itemRc; }					//아이템 렉트값 넘기기
	ITEMSTATE getitemstate() { return _itemState; }			//아이템 enum값 넘기기
};