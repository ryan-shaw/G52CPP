#include "header.h"

#include "PlayerWall.h"
#include "BouncingBallMain.h"

	// Constructor has to set up all of the position and size members
	PlayerWall::PlayerWall(BouncingBallMain* pEngine )
		: DisplayableObject( pEngine )
	{
		// The ball coordinate will be the centre of the ball
		// Because we start drawing half the size to the top-left.
		m_iStartDrawPosX = -40;
		m_iStartDrawPosY = -3;
		// Record the ball size as both height and width
		m_iDrawWidth = 80;
		m_iDrawHeight = 6;
		// Just put it somewhere initially
		//m_dX = m_iPreviousScreenX = m_iCurrentScreenX = m_iDrawWidth;
		//m_dY = m_iPreviousScreenY = m_iCurrentScreenY = m_iDrawHeight;

		m_dX = m_iPreviousScreenX = m_iCurrentScreenX = (pEngine->GetScreenWidth()/2);
		m_dY = m_iPreviousScreenY = m_iCurrentScreenY = pEngine->GetScreenHeight()-10;
		// Speed
		m_dSX = 0;
		m_dSY = 0;
		// And make it visible
		SetVisible(true);
	}

	// Draw the shape - just draws a rectangle
	void PlayerWall::Draw()
	{
		GetEngine()->DrawScreenRectangle( 
			m_iCurrentScreenX - m_iDrawWidth/2 + 1,
			m_iCurrentScreenY - m_iDrawHeight/2 + 1,
			m_iCurrentScreenX + m_iDrawWidth/2 -1,
			m_iCurrentScreenY + m_iDrawHeight/2 -1,
			0xffff00 );

		// This will store the position at which the object was drawn
		// so that the background can be drawn over the top.
		// This will then remove the object from the screen.
		StoreLastScreenPositionAndUpdateRect();
	}

	// Called frequently, this should move the item
	// In this case we also accept cursor key presses to change the speed
	// Space will set the speed to zero
	void PlayerWall::DoUpdate( int iCurrentTime )
	{
		if(m_dSX > 0)
			m_dSX -= 0.0001;
		if(m_dSX < 0)
			m_dSX += 0.0001;
		if ( GetEngine()->IsKeyPressed( SDLK_LEFT ) )
			m_dSX -= 0.001;
		if ( GetEngine()->IsKeyPressed( SDLK_RIGHT ) )
			m_dSX += 0.001;
		if ( GetEngine()->IsKeyPressed( SDLK_SPACE ) )
			m_dSX = m_dSY = 0;
		printf("%f\n", m_dSX);
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

/*
PlayerWall::PlayerWall(BouncingBallMain* pEngine) : DisplayableObject(pEngine), m_pEngine(pEngine)
{

	m_iStartDrawPosX = -40;
	m_iStartDrawPosY = -3;
	// Record the ball size as both height and width
	m_iDrawWidth = 80;
	m_iDrawHeight = 6;
	// Just put it somewhere initially
	m_iPreviousScreenX = m_iCurrentScreenX = (pEngine->GetScreenWidth()/2);
	m_iPreviousScreenY = m_iCurrentScreenY = pEngine->GetScreenHeight()-10;

	//m_iCurrentScreenX = (pEngine->GetScreenWidth()/2);
	//m_iCurrentScreenY = pEngine->GetScreenHeight()-10;
}

PlayerWall::~PlayerWall(void)
{
	
}

void PlayerWall::Draw()
{
	//printf("%d %d\n", m_iCurrentScreenX, m_iCurrentScreenY);
	m_pEngine->DrawScreenRectangle(
		m_iCurrentScreenX - m_iDrawWidth/2	+ 1, 
		m_iCurrentScreenY - m_iDrawHeight/2 + 1, 
		m_iCurrentScreenX + m_iDrawWidth/2	- 1, 
		m_iCurrentScreenY + m_iDrawHeight/2 - 1, 
		0xffffff);
	StoreLastScreenPositionAndUpdateRect();

}

void PlayerWall::DoUpdate(int iCurrentTime)
{
	if ( GetEngine()->IsKeyPressed( SDLK_LEFT ) )
		if(iCurrentTime % 100)
			m_iCurrentScreenX -= 1+0.5;
	if ( GetEngine()->IsKeyPressed( SDLK_RIGHT ) ){
		if(iCurrentTime % 100)
			m_iCurrentScreenX += 1+0.5;
	}

	//printf("X: %d, Y: %d\n", m_iCurrentScreenX, m_iCurrentScreenY);
		
	RedrawObjects();
}*/