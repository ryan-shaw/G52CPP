#include "header.h"

#include "BouncingBall.h"
#include "BouncingBallMain.h"
#include "PlayerWall.h"


/** Constructor */
BouncingBall::BouncingBall( BouncingBallMain* pEngine, int iID, 
							int iDrawType, int iSize, int iColour,
							char* szLabel, 
							int iXLabelOffset, int iYLabelOffset)
: DisplayableObject( pEngine )
, m_pEngine( pEngine )
, m_iID(iID)
, m_iDrawType(iDrawType)
, m_iSize(iSize)
, m_iColour(iColour)
, m_szLabel(szLabel)
, m_iXLabelOffset(iXLabelOffset)
, m_iYLabelOffset(iYLabelOffset)
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

	// If there is a label then draw the text
	if ( (m_szLabel!=NULL) && (strlen(m_szLabel)>0) )
	{
		//GetEngine()->DrawString( iCentreX+m_iXLabelOffset+1, iCentreY+m_iYLabelOffset+1, m_szLabel, 0xffffff );
		//GetEngine()->DrawScreenString( iCentreX+m_iXLabelOffset, iCentreY+m_iYLabelOffset, m_szLabel, uiColourText );
	}

	// Store the position at which the object was last drawn
	// You MUST do this to ensure that the screen is updated when only drawing movable objects
	// This tells the system where to 'undraw' the object from
	StoreLastScreenPositionAndUpdateRect();
}

/**
Handle the update action, moving the object and/or handling any game logic
*/
void BouncingBall::DoUpdate( int iCurrentTime )
{
	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}

/** Constructor */
BouncingBall2::BouncingBall2( BouncingBallMain* pEngine, int iID, 
							int iDrawType, int iSize, int iColour,
							char* szLabel, 
							int iXLabelOffset, int iYLabelOffset)
: BouncingBall( pEngine, iID, iDrawType, iSize, iColour, szLabel, iXLabelOffset, iYLabelOffset )
, m_dX( iSize )
, m_dY( iSize )
, m_dSX(0)
, m_dSY(0)
{
}

void BouncingBall2::SetPosition( double dX, double dY )
{
	m_dX = dX;
	m_dY = dY;
}

void BouncingBall2::SetSpeed( double dSX, double dSY )
{
	m_dSX = dSX;
	m_dSY = dSY;
}

/**
Handle the update action, moving the object and/or handling any game logic
*/
void BouncingBall2::DoUpdate( int iCurrentTime )
{
	/*if ( GetEngine()->IsKeyPressed( SDLK_UP ) )
		m_dSY -= 0.01;
	if ( GetEngine()->IsKeyPressed( SDLK_DOWN ) )
		m_dSY += 0.01;
	if ( GetEngine()->IsKeyPressed( SDLK_LEFT ) )
		m_dSX -= 0.01;
	if ( GetEngine()->IsKeyPressed( SDLK_RIGHT ) )
		m_dSX += 0.01;
	if ( GetEngine()->IsKeyPressed( SDLK_SPACE ) )
		m_dSX = m_dSY = 0;
		*/

	DisplayableObject* pObject;
	for ( int iObjectId = 0 ; 
		 (pObject = GetEngine()->GetDisplayableObject( iObjectId )
				) != NULL ;
		iObjectId++ )
	{
		if ( pObject == this ) // This is us, skip it
			continue;
		PlayerWall* o = (PlayerWall*) pObject;

		// If you need to cast to the sub-class type, you must use dynamic_cast, see lecture 19
		// We are just using base class parts
		int iXDiff = pObject->GetXCentre() - m_iCurrentScreenX;
		int iYDiff = pObject->GetYCentre() - o->m_iDrawHeight*2 - m_iCurrentScreenY;
		
		int oXBound1 = o->GetXCentre() - o->m_iDrawWidth/2;
		int oXBound2 = o->GetXCentre() + o->m_iDrawWidth/2;

		int oYBound1 = o->GetYCentre() - o->m_iDrawHeight/2;
		int oYBound2 = o->GetYCentre() + o->m_iDrawHeight/2;

		if(iYDiff == 0)
			m_dSY = -m_dSY;

		printf("DiffX: %d, DiffY: %d\n", iXDiff, iYDiff);

		// Estimate the size - by re-calculating it
		int iTick = iCurrentTime/20; // 1 per 20ms
		int iFrame = iTick % 30;
		int iSize = 10 + iFrame;
		if ( iFrame > 15 )
			iSize = 10 + (30-iFrame);
		int iSizeOther = iSize; // Assume both the same size

		// Pythagorus' theorum:
		if ( ((iXDiff*iXDiff)+(iYDiff*iYDiff)) 
				< ((iSizeOther+iSize)*(iSizeOther+iSize)) )
		{
		
			RedrawObjects();
		}
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
			m_dSY = -m_dSY;
	}

	if ( (m_dY+m_iStartDrawPosY+m_iDrawHeight) > (GetEngine()->GetScreenHeight()-1) )
	{
		m_dY = GetEngine()->GetScreenHeight() -1 - m_iStartDrawPosY - m_iDrawHeight;
		if ( m_dSY > 0 )
			m_dSY = -m_dSY;
	}

	// Work out current position
	m_iCurrentScreenX = (int)(m_dX+0.5);
	m_iCurrentScreenY = (int)(m_dY+0.5);

	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}

