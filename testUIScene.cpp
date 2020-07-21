#include "stdafx.h"
#include "testUIScene.h"

HRESULT testUIScene::init()
{
	_ui = new ui;
	_ui->init();

	return S_OK;
}

void testUIScene::render()
{
	_ui->render();
}

void testUIScene::update()
{
	_ui->update();
}

void testUIScene::release()
{
	SAFE_DELETE(_ui);
}
