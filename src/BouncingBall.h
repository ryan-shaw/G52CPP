#ifndef BouncingBall_H
#define BouncingBall_H

#include "DisplayableObject.h"
#include "MovementPosition.h"

#include "BouncingBallMain.h"

class BaseEngine;

class BouncingBall :
	public DisplayableObject
{
public:
	BouncingBall(BouncingBallMain* pEngine, int iID, 
		int iDrawType, int iSize, int iColour);

	virtual ~BouncingBall(void);
	void SetPosition( double dX, double dY );

	void SetSpeed( double dSX, double dSY );

	void Draw();

	void DoUpdate( int iCurrentTime );
	// Size of thing to draw
	int m_iSize;

	//int iCentreX = m_iCurrentScreenX + m_iStartDrawPosX + m_iDrawWidth/2;
	//int iCentreY = m_iCurrentScreenY + m_iStartDrawPosY + m_iDrawHeight/2;
private:
	/** Pointer to the main engine object */
	BouncingBallMain* m_pEngine;

	// Unique id for object, passed to engine to identify it
	int m_iID;

	// Type of thing to draw
	int m_iDrawType;

	// Colour index to draw with
	int m_iColour;

protected:
	double m_dX;
	double m_dY;
	double m_dSX;
	double m_dSY;
};

#endif
