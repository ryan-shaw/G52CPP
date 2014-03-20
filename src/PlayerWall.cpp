#include "header.h"

#include "PlayerWall.h"
#include "BouncingBallMain.h"

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
}