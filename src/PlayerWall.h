#ifndef PlayerWall_H
#define PlayerWall_H

#include "DisplayableObject.h"
#include "MovementPosition.h"

#include "BouncingBallMain.h"

class BaseEngine;

class PlayerWall : public DisplayableObject
{
public:
	PlayerWall(BouncingBallMain* pEngine, bool pos);
	
	//virtual ~PlayerWall(void);

	void Draw();

	void DoUpdate( int iCurrentTime );

	int GetDrawWidth(){return m_iDrawWidth;}
	int GetDrawHeight(){return m_iDrawHeight;}
	bool GetPlayer(){return pos;}
protected:
	double m_dX;
	double m_dY;
	double m_dSX;
	double m_dSY;
	bool pos;
private:
	BouncingBallMain* m_pEngine;
};

#endif