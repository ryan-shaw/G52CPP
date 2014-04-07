#include "header.h"

#include "BouncingBall.h"
#include "BouncingBallMain.h"
#include "PlayerWall.h"


/** Constructor */
BouncingBall::BouncingBall( BouncingBallMain* pEngine, int iID, 
							int iDrawType, int iSize, int iColour)
: DisplayableObject( pEngine )
, m_pEngine( pEngine )
, m_iID(iID)
, m_iDrawType(iDrawType)
, m_iSize(iSize)
, m_iColour(iColour)

{
	// The ball coordinate will be the centre of the ball
	// Because we start drawing half the size to the top-left.
	m_iStartDrawPosX = -m_iSize/2;
	m_iStartDrawPosY = -m_iSize/2;

	// Record the ball size as both height and width
	m_iDrawWidth = m_iSize;
	m_iDrawHeight = m_iSize;
	
	// Just put it somewhere initially
	m_iPreviousScreenX = m_iCurrentScreenX = m_iDrawWidth;
	m_iPreviousScreenY = m_iCurrentScreenY = m_iDrawHeight;

	// And make it visible
	SetVisible(true);
}

/** Destructor */
BouncingBall::~BouncingBall(void)
{
}

/**
Draw the player object.
Could be a simple shape but this makes a fake ball shape and labels it.
*/
void BouncingBall::Draw()
{
	// Do not draw if it should not be visible
	if ( !IsVisible() )
		return;

	unsigned int uiColourMult = 0x010001;
	unsigned int uiColourText = 0xffffff;

	// Choose one of 8 colours:
	switch( m_iColour % 8 )
	{ 
	case 1: uiColourMult = 0x010000; uiColourText = 0xffffff; break;
	case 2: uiColourMult = 0x000100; uiColourText = 0xffffff; break;
	case 3: uiColourMult = 0x000001; uiColourText = 0xffffff; break;
	case 4: uiColourMult = 0x010001; uiColourText = 0; break;
	case 5: uiColourMult = 0x010100; uiColourText = 0; break;
	case 6: uiColourMult = 0x000101; uiColourText = 0; break;
	case 7: uiColourMult = 0x010101; uiColourText = 0; break;
	default: uiColourMult = 0x000000; break;
	}

	// Concentric circles for pseudo-sphere
	int iRadiusSquared = (m_iDrawWidth/2) * (m_iDrawWidth/2);
	int iCentreX = m_iCurrentScreenX + m_iStartDrawPosX + m_iDrawWidth/2;
	int iCentreY = m_iCurrentScreenY + m_iStartDrawPosY + m_iDrawHeight/2;
	for ( int iX = m_iCurrentScreenX + m_iStartDrawPosX ; iX < (m_iCurrentScreenX + m_iStartDrawPosX + m_iDrawWidth) ; iX++ )
		for ( int iY = m_iCurrentScreenY + m_iStartDrawPosY ; iY < (m_iCurrentScreenY + m_iStartDrawPosY + m_iDrawHeight) ; iY++ )
			if ( ( (iX-iCentreX)*(iX-iCentreX) + (iY-iCentreY)*(iY-iCentreY) ) <= iRadiusSquared )
			{
				// 0xB0 is the range of values, 0xff is the brightest value.
				unsigned int uiColour = (0xB0 * ((iX-iCentreX)*(iX-iCentreX) + (iY-iCentreY)*(iY-iCentreY))) / iRadiusSquared;
				uiColour = 0xff - uiColour;
				GetEngine()->SafeSetScreenPixel( iX, iY, uiColourMult * uiColour );
			}

	StoreLastScreenPositionAndUpdateRect();
}



void BouncingBall::SetPosition( double dX, double dY )
{
	m_dX = dX;
	m_dY = dY;
}

void BouncingBall::SetSpeed( double dSX, double dSY )
{
	m_dSX = dSX;
	m_dSY = dSY;
}

/**
Handle the update action, moving the object and/or handling any game logic
*/

bool collide(int x, int x1, int y, int y1,/* colliding object */ int xx, int xx1, int yy, int yy1){
	if(x >= xx && x1 <= xx1 && y >= yy && y1 <= yy1)
		return true;
	return false;
}
void BouncingBall::DoUpdate( int iCurrentTime )
{
	DisplayableObject* pObject;
	for(int iObjectId = 0; (pObject = GetEngine()->GetDisplayableObject( iObjectId )) != NULL ; iObjectId++ )
	{
		if ( pObject == this ) // This is us, skip it
			continue;
		PlayerWall* o = (PlayerWall*) pObject; // We have no other objects so point checking if it's not a player wall

		//int iXDiff = pObject->GetXCentre() - (o->GetDrawWidth()/2) - m_iCurrentScreenX + m_iSize/2;
		//int iYDiff = pObject->GetYCentre() - o->GetDrawHeight()*2 - m_iCurrentScreenY + m_iSize/2;

		int xx = o->GetXCentre() - (o->GetDrawWidth()/2);
		int xx1 = o->GetXCentre() + (o->GetDrawWidth()/2);
		int yy = o->GetYCentre() - (o->GetDrawHeight()/2);
		int yy1 = o->GetYCentre() + (o->GetDrawHeight()/2);
	
		int x = m_iCurrentScreenX + m_iStartDrawPosX + m_iDrawWidth/2;
		int x1 = m_iCurrentScreenX + m_iStartDrawPosX + m_iDrawWidth/2;

		int y = m_iCurrentScreenY + m_iStartDrawPosY + m_iDrawHeight/2;
		int y1 = m_iCurrentScreenY + m_iStartDrawPosY + m_iDrawHeight/2;

		//if(!o->GetPlayer())
		//	printf("Y: %d, Y1: %d, YY: %d, YY1: %d\n", y, y1, yy, yy1);
		if(collide(x, x1, y, y1, xx, xx1, yy, yy1)){
			if(o->GetPlayer()){ //Bot player
				m_dSY = -m_dSY;
				float diff = (pObject->GetXCentre() - m_iCurrentScreenX)/400.0; // Bounce angle relative to hit position, lower denomenator means higher angle
				m_dSY -= 0.04; // Increase speed
				m_dSX += -diff; // Change horizontal speed
			}else{ // Top player
				m_dSY = -m_dSY;
				float diff = (pObject->GetXCentre() - m_iCurrentScreenX)/400.0; 
				m_dSY += 0.04;
				m_dSX += -diff;
				//printf("Collide");
			}
		}
		//	printf("Collided");
		/*
		// Collision
		if(iYDiff == 0 && iXDiff <= 10 && iXDiff >= -80){
			m_dSY = -m_dSY;
			float diff = (pObject->GetXCentre() - m_iCurrentScreenX)/400.0; // Bounce angle relative to hit position, lower denomenator means higher angle
			m_dSY -= 0.04; // Increase speed
			m_dSX += -diff; // Change horizontal speed
		}
		if(iXDiff <= 13 && iXDiff >= -80 && iYDiff == -13){
			m_dSY = -m_dSY;
			float diff = (pObject->GetXCentre() - m_iCurrentScreenX)/400.0; 
			m_dSY += 0.04;
			m_dSX += -diff;
		}
		// End collision*/

		//RedrawObjects();
	}

	m_dX += m_dSX;
	m_dY += m_dSY;

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
			m_dSX = m_dSY = 0; // Game over, bot player wins
	}

	if ( (m_dY+m_iStartDrawPosY+m_iDrawHeight) > (GetEngine()->GetScreenHeight()-1) )
	{
		m_dY = GetEngine()->GetScreenHeight() -1 - m_iStartDrawPosY - m_iDrawHeight;
		if ( m_dSY > 0 ){
			m_dSX = m_dSY = 0; // Game over, top player wins
		}
	}

	// Work out current position
	m_iCurrentScreenX = (int)(m_dX+0.5);
	m_iCurrentScreenY = (int)(m_dY+0.5);

	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
	
}

