#include "PlayerWallAI.h"
#include "PlayerWall.h"
#include "BouncingBall.h"

PlayerWallAI::PlayerWallAI(BouncingBallMain* pEngine, bool pos) : PlayerWall(pEngine, pos)
{
	printf("Created AI player\n");
}

PlayerWallAI::~PlayerWallAI()
{
}

void PlayerWallAI::DoUpdate(int iCurrentTime){
	if(m_dSX > 0)
		m_dSX -= 0.0001;
	if(m_dSX < 0)
		m_dSX += 0.0001;
	if(pos){
		if ( GetEngine()->IsKeyPressed( SDLK_LEFT ) )
			m_dSX -= 0.001;
		if ( GetEngine()->IsKeyPressed( SDLK_RIGHT ) )
			m_dSX += 0.001;
		if ( GetEngine()->IsKeyPressed( SDLK_SPACE ) )
			m_dSX = m_dSY = 0;
	}else{
		if ( GetEngine()->IsKeyPressed( SDLK_a ) )
			m_dSX -= 0.001;
		if ( GetEngine()->IsKeyPressed( SDLK_d ) )
			m_dSX += 0.001;
		if ( GetEngine()->IsKeyPressed( SDLK_SPACE ) )
			m_dSX = m_dSY = 0;
	}
	// We want to get the difference from the ball, lets also get the speed we need to travel but lets set a max speed
	//BouncingBall * ball = m_pEngine->GetBall();
	//int xDiff = ball->GetXCentre() - GetXCentre(); 

//	printf("%d\n", xDiff);

	DisplayableObject* pObject;
	for(int iObjectId = 0; (pObject = GetEngine()->GetDisplayableObject( iObjectId )) != NULL ; iObjectId++ )
	{
		if ( pObject == this ) // This is us, skip it
			continue;
		BouncingBall * p = dynamic_cast<BouncingBall*> (pObject);
		if(p != 0){
			int maxSpeed = 1; // Max
			int xDiff = p->GetXCentre()-GetXCentre();
			bool side; // True = right, false = left
			if(xDiff > 0)
				side = false;
			else {
				side = true;
				xDiff = -xDiff;
			}
			float speed = ((xDiff/150.0) > maxSpeed) ? maxSpeed : (xDiff/150.0);
			printf("%f\n", speed);
			if(!side)
				m_dSX = speed;
			else
				m_dSX = -speed;
		}
	}
	if(m_dSX < -0.7)
		m_dSX = -0.7;
	if(m_dSX > 0.7)
		m_dSX = 0.7;
	// Alter position for speed
	m_dX += m_dSX;
	m_dY += m_dSY;

	// Check for bounce off the edge
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
	if ( (m_dY+m_iStartDrawPosY) < 0 )
	{
		m_dY = -m_iStartDrawPosY;
		if ( m_dSY < 0 )
			m_dSY = -m_dSY;
	}
	if ( (m_dY+m_iStartDrawPosY+m_iDrawHeight) > (GetEngine()->GetScreenHeight()-1) )
	{
		m_dY = GetEngine()->GetScreenHeight() -1 - m_iStartDrawPosY - m_iDrawHeight;
		if ( m_dSY > 0 )
			m_dSY = -m_dSY;
	}

	// Set current position - you NEED to set the current positions
	m_iCurrentScreenX = (int)(m_dX+0.5);
	m_iCurrentScreenY = (int)(m_dY+0.5);

	//printf("Position %f, %f\n", m_dX, m_dY );

	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}