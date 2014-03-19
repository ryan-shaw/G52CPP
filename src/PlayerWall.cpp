#include "header.h"

#include "PlayerWall.h"
#include "BouncingBallMain.h"

PlayerWall::PlayerWall(BouncingBallMain* pEngine) : DisplayableObject(pEngine), m_pEngine(pEngine)
{
	m_iDrawHeight = 5;
	m_iDrawWidth = 80;
	m_iCurrentScreenX = (pEngine->GetScreenWidth()/2);
	m_iCurrentScreenY = pEngine->GetScreenHeight()-10;
}

PlayerWall::~PlayerWall(void)
{
	
}

void PlayerWall::Draw()
{
	//printf("%d %d\n", m_iCurrentScreenX, m_iCurrentScreenY);
	m_pEngine->DrawScreenRectangle(m_iCurrentScreenX-m_iDrawWidth/2, m_iCurrentScreenY-m_iDrawHeight/2, m_iCurrentScreenX+m_iDrawWidth/2, m_iCurrentScreenY+m_iDrawHeight/2, 0xffffff);
}

void PlayerWall::DoUpdate(int iCurrentTime)
{
	RedrawObjects();
}