#include <stdlib.h> // So we can have random
#include "DisplayableObject.h"
#include "MovementPosition.h"

#include "PongMain.h"

class BaseEngine;

class Ball :
	public DisplayableObject
{
public:
	Ball(PongMain* pEngine, int iID, 
		int iDrawType, int iSize, int iColour);

	virtual ~Ball(void);
	void SetPosition( double dX, double dY );

	void SetSpeed( double dSX, double dSY );

	void Draw();

	void DoUpdate( int iCurrentTime );

private:
	/** Pointer to the main engine object */
	PongMain* m_pEngine;

	// Unique id for object, passed to engine to identify it
	int m_iID;

	// Type of thing to draw
	int m_iDrawType;

	// Colour index to draw with
	int m_iColour;

	int m_iSize;

protected:
	double m_dX;
	double m_dY;
	double m_dSX;
	double m_dSY;
};


