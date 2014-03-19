#ifndef PlayerWall_H
#define PlayerWall_H

#include "DisplayableObject.h"
#include "MovementPosition.h"

#include "BouncingBallMain.h"

class BaseEngine;

class PlayerWall : public DisplayableObject
{
public:
	PlayerWall(BouncingBallMain* pEngine);
	
	virtual ~PlayerWall(void);

	void Draw();

	void DoUpdate( int iCurrentTime );

	int m_iDrawWidth;
	int m_iDrawHeight;
private:
	BouncingBallMain* m_pEngine;
};

#endif