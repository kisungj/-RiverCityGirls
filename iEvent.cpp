#include "stdafx.h"
#include "iEvent.h"

iCameraMove::iCameraMove(POINTFLOAT targetLocation, float speed, bool* arg)
{
	mTargetLocation = targetLocation;
	mSpeed = speed;
	_isEnd = arg;
}

void iCameraMove::eventStart()
{
}

bool iCameraMove::eventUpdate()
{
	POINTFLOAT position;
	position.x = CAMERAMANAGER->getX();
	position.y = CAMERAMANAGER->getY();
	float angle = getAngle(position.x, position.y, mTargetLocation.x, mTargetLocation.y);

	CAMERAMANAGER->setX(CAMERAMANAGER->getX() + cos(angle) * mSpeed * TIMEMANAGER->getElapsedTime());
	CAMERAMANAGER->setY(CAMERAMANAGER->getY() - sin(angle) * mSpeed * TIMEMANAGER->getElapsedTime());

	if (getDistance(position.x, position.y, mTargetLocation.x, mTargetLocation.y) < 50)
	{
		CAMERAMANAGER->setX(mTargetLocation.x);
		CAMERAMANAGER->setY(mTargetLocation.y);

		*_isEnd = true;
		return true;
	}

	return false;
}

iWaitForSecond::iWaitForSecond(float timer)
{
	_timer = 0;
	_maxTimer = timer;
}

void iWaitForSecond::eventStart()
{
}

bool iWaitForSecond::eventUpdate()
{
	_timer++;

	if (_timer > _maxTimer)
	{
		return true;
	}

	return false;
}
