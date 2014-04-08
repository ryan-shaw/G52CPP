#include "header.h"

#include "PlayerWall.h"
#include "PongMain.h"

	// Constructor has to set up all of the position and size members
	PlayerWall::PlayerWall(PongMain* pEngine, bool pos) // true = bot, false = top
		: DisplayableObject( pEngine ), m_bPos(pos), m_pEngine(pEngine)
	{
		m_iScore = 0;

		m_iStartDrawPosX = -40;
		m_iStartDrawPosY = -3;
		// Record the ball size as both height and width
		m_iDrawWidth = 80;
		m_iDrawHeight = 6;

		m_dX = m_iPreviousScreenX = m_iCurrentScreenX = (pEngine->GetScreenWidth()/2);
		m_dY = m_iPreviousScreenY = m_iCurrentScreenY = pos ? pEngine->GetScreenHeight()-10 : 10;
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

		StoreLastScreenPositionAndUpdateRect();
	}

	void PlayerWall::IncreaseScore(int amount){
		m_iScore += amount;
	}

	void PlayerWall::DoUpdate( int iCurrentTime )
	{
		if(iCurrentTime % 500 == 0)
			IncreaseScore(1);

		if(m_dSX > 0) // Gives the gliding effect to the walls
			m_dSX -= 0.0001;
		if(m_dSX < 0)
			m_dSX += 0.0001;
		if(m_bPos){ // Movement of walls for each player
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
	
		// Max speed
		if(m_dSX < -0.7)
			m_dSX = -0.7;
		if(m_dSX > 0.7)
			m_dSX = 0.7;
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

		// Set current position - you NEED to set the current positions
		m_iCurrentScreenX = (int)(m_dX+0.5);
		m_iCurrentScreenY = (int)(m_dY+0.5);

		// Ensure that the object gets redrawn on the display, if something changed
		RedrawObjects();
	}