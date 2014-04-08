#ifndef PlayerWall_H
#define PlayerWall_H

#include "DisplayableObject.h"
#include "MovementPosition.h"

#include "PongMain.h"

class BaseEngine;

class PlayerWall : public DisplayableObject
{
public:
	PlayerWall(PongMain* pEngine, bool pos);
	
	//virtual ~PlayerWall(void);

	void Draw();

	void DoUpdate( int iCurrentTime );

	int GetDrawWidth(){return m_iDrawWidth;}
	int GetDrawHeight(){return m_iDrawHeight;}
	bool GetPlayer(){return m_bPos;}
	void IncreaseScore(int);
	int GetScore(){return m_iScore;}
protected:
	double m_dX;
	double m_dY;
	double m_dSX;
	double m_dSY;
	bool m_bPos;
	int m_iLives;
	int m_iScore;
private:
	PongMain* m_pEngine;
};

#endif