#pragma once
#include "baseengine.h"
class BaseAMain :
	public BaseEngine
{
public:
	BaseAMain(void);
	~BaseAMain(void);
	void SetupBackgroundBuffer(void);
	void MouseDown(int iButton, int iX, int iY);
	void KeyDown(int aKeyCode);
};

