#include "header.h"

#include "BaseEngine.h"

#include "BouncingBall.h"

#include "PlayerWall.h"

#include "BouncingBallMain.h"

#include "JPGImage.h"

#include "TileManager.h"

/*
Draw the background of the screen.
This fills the background with black
Then puts some random colour on it
Then demos various ways of drawing shapes, images, etc
*/
void BouncingBallMain::SetupBackgroundBuffer()
{
	FillBackground( 0 );

	for ( int iX = 0 ; iX < GetScreenWidth() ; iX++ )
		for ( int iY = 0 ; iY < this->GetScreenHeight() ; iY++ )
			switch( rand()%100 )
			{
			case 0: SetBackgroundPixel( iX, iY, 0xFF0000 ); break;
			case 1: SetBackgroundPixel( iX, iY, 0x00FF00 ); break;
			case 2: SetBackgroundPixel( iX, iY, 0x0000FF ); break;
			case 3: SetBackgroundPixel( iX, iY, 0xFFFF00 ); break;
			case 4: SetBackgroundPixel( iX, iY, 0x00FFFF ); break;
			case 5: SetBackgroundPixel( iX, iY, 0xFF00FF ); break;
		}

}


/*
In here you need to create any movable objects that you wish to use.
Sub-classes need to implement this function.
*/
int BouncingBallMain::InitialiseObjects()
{
	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();

	// Destroy any existing objects
	DestroyOldObjects();

	//m_pWall1 = new PlayerOneWall();

	// Create another, different, type of ball
	m_pBall2 = new BouncingBall2( this, 
		0/*Id*/, 1/*Type*/, 
		15/*Size*/, 
		2/*Colour*/,
		"B"/*Label*/, 
		-10/*XLabelOffset*/,
		-15/*YLabelOffset*/ );
	m_pBall2->SetPosition( 100,100 );
	m_pBall2->SetSpeed( 0.01, 0.01 );

	// And a third ball
	m_pBall3 = new BouncingBall2( this, 
		0/*Id*/, 1/*Type*/, 
		15/*Size*/, 
		3/*Colour*/,
		"C"/*Label*/, 
		-10/*XLabelOffset*/,
		-15/*YLabelOffset*/ );
	m_pBall3->SetPosition( 300,250 );
	m_pBall3->SetSpeed( 0.8,1.2 );

	m_pWall1 = new PlayerWall(this);



	// Create an array one element larger than the number of objects that you want.
	m_ppDisplayableObjects = new DisplayableObject*[3]; // i.e. 3 balls + 1 for NULL

	// You MUST set the array entry after the last one that you create to NULL, so that the system knows when to stop.
	m_ppDisplayableObjects[0] = m_pBall2;
	m_ppDisplayableObjects[1] = m_pWall1;

	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in order to work out where the end of the array is.
	m_ppDisplayableObjects[2] = NULL;

	// NOTE: We also need to destroy the objects, but the method at the 
	// top of this function will destroy all objects pointed at by the 
	// array elements so we can ignore that here.

	return 0;
}







/* Draw text labels */
void BouncingBallMain::DrawStrings()
{
	CopyBackgroundPixels( 0/*X*/, 0/*Y*/, GetScreenWidth(), 30/*Height*/ );
	DrawScreenString( 150, 10, "Example text", 0xffffff, NULL );
	SetNextUpdateRect( 0/*X*/, 0/*Y*/, GetScreenWidth(), 30/*Height*/ );
}


/* Overridden GameAction to ensure that objects use the modified time */
void BouncingBallMain::GameAction()
{
	// If too early to act then do nothing
	if ( !TimeToAct() )
		return;

	// Don't act for another 10 ticks
	SetTimeToAct( 1 );

	UpdateAllObjects( GetTime() );
}


// Override to add a node at specified point
void BouncingBallMain::MouseDown( int iButton, int iX, int iY )
{
	m_pBall2->SetPosition( iX, iY );
}

/*
Handle any key presses here.
Note that the objects themselves (e.g. player) may also check whether a key is pressed
*/
void BouncingBallMain::KeyDown(int iKeyCode)
{
	switch ( iKeyCode )
	{
	case SDLK_ESCAPE: // End program when escape is pressed
		SetExitWithCode( 0 );
		break;
	case SDLK_SPACE: // SPACE Pauses
		break;
	}
}

