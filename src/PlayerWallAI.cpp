#include "PlayerWallAI.h"
#include "PlayerWall.h"
#include "Ball.h"

PlayerWallAI::PlayerWallAI(PongMain* pEngine, bool bPos, Ball* pBall) : PlayerWall(pEngine, bPos), m_pBall(pBall)
{
}

PlayerWallAI::~PlayerWallAI()
{
}

void PlayerWallAI::DoUpdate(int iCurrentTime){

	if(iCurrentTime % 500 == 0)
			IncreaseScore(1);

	if(m_dSX > 0)
		m_dSX -= 0.0001;
	if(m_dSX < 0)
		m_dSX += 0.0001;
	
	double maxSpeed = 0.7; // Max
	int xDiff = m_pBall->GetXCentre() - GetXCentre();
	bool side; // True = right, false = left
	if(xDiff > 0)
		side = false;
	else {
		side = true;
		xDiff = -xDiff;
	}
	double speed = ((xDiff/150.0) > maxSpeed) ? maxSpeed : (xDiff/150.0);
	if(!side)
		m_dSX = speed;
	else
		m_dSX = -speed;
		
	// Alter position for speed
	m_dX += m_dSX;
	m_dY += m_dSY;

	// Check for bounce off the edge, only need to check X bounces, it will never move along y axis
	if ( (m_dX+m_iStartDrawPosX) < 0 )
	{
		m_dX = - m_iStartDrawPosX;
		if ( m_dSX < 0 )
			m_dSX = -m_dSX;
	}
	if ( (m_dX+m_iStartDrawPosX+m_iDrawWidth) > (GetEngine()->GetScreenWidth()-1) )
	{
		m_dX = GetEngine()->GetScreenWidth() -1 - m_iStartDrawPosX - m_iDrawWidth;
		if ( m_dSX > 0 )
			m_dSX = -m_dSX;
	}

	m_iCurrentScreenX = (int)(m_dX+0.5);
	m_iCurrentScreenY = (int)(m_dY+0.5);

	RedrawObjects();
}