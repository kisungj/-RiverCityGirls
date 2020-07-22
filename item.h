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
	string		_itemName;			//아이템 이름
	string		_itemDiscription;	//아이템 설명

	float _x, _y;					//아이템 위치값
	float _gravity;					//아이템 떨어지는 중력값

	int _hpPortion;					//HP 증가량
	int _powerPortion;				//공격력 증가량

	bool _gravityBool;				//아이템 떨어지는 불값

public:
	Item();
	~Item();

	virtual HRESULT init(ITEMSTATE itemstate);
	virtual HRESULT init(ITEMSTATE itemstate, POINT position);
	virtual void update();
	virtual void release();
	virtual void render();

	void move();											 //아이템 드랍시 떨어지게

	image* getItemImage() { return _itemImg; }
	RECT getItemRc() { return _itemRc; }					 //아이템 렉트값 넘기기
	ITEMSTATE getitemstate() { return _itemState; }			 //아이템 enum값 넘기기
	string getItemName() { return _itemName; }				 //아이템 이름값 넘기기
	string getItemDiscription() { return _itemDiscription; } //아이템 설명값 넘기기
	int getHpPortion() { return _hpPortion; }				 //HP포션 값 넘기기
	int getPowerPortion() { return _powerPortion; }			 //파워포션 값 넘기기

};