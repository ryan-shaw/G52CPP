#include "header.h"

#include "BaseEngine.h"

#include "BouncingBall.h"

#include "PlayerWall.h"

#include "BouncingBallMain.h"

#include "JPGImage.h"

#include "TileManager.h"

#include "Network.h"

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
	//Network network;
	//network.InitNetwork();
	// Load the font
	font=TTF_OpenFont("Cornerstone Regular.ttf", 10);

	

	return 0;
}

void BouncingBallMain::AddObjects()
{
	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();

	// Destroy any existing objects
	DestroyOldObjects();

	//m_pWall1 = new PlayerOneWall();

	// Create another, different, type of ball
	m_pBall = new BouncingBall( this, 
		0/*Id*/, 1/*Type*/, 
		15/*Size*/, 
		2/*Colour*/,
		"B"/*Label*/, 
		-10/*XLabelOffset*/,
		-15/*YLabelOffset*/ );
	m_pBall->SetPosition( 100,100 );
	m_pBall->SetSpeed( 0.1, 0.1);

	m_pWall1 = new PlayerWall(this, true);
	m_pWall2 = new PlayerWall(this, false);


	// Create an array one element larger than the number of objects that you want.
	m_ppDisplayableObjects = new DisplayableObject*[4]; // i.e. 3 balls + 1 for NULL

	// You MUST set the array entry after the last one that you create to NULL, so that the system knows when to stop.
	m_ppDisplayableObjects[0] = m_pBall;
	m_ppDisplayableObjects[1] = m_pWall1;
	m_ppDisplayableObjects[2] = m_pWall2;

	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in order to work out where the end of the array is.
	m_ppDisplayableObjects[3] = NULL;

	// NOTE: We also need to destroy the objects, but the method at the 
	// top of this function will destroy all objects pointed at by the 
	// array elements so we can ignore that here.
}

/* Draw text labels */
void BouncingBallMain::DrawStrings()
{
	CopyBackgroundPixels( 0/*X*/, 0/*Y*/, GetScreenWidth(), 150/*Height*/ );
	if(menu){
		int w,h;
		TTF_SizeUTF8(font, "Main Menu", &w, &h);
		DrawScreenString( GetScreenWidth()/2-(w), 10, "Main Menu", 0xffffff, NULL );

		TTF_SizeUTF8(font, "vs Computer", &w, &h);
		DrawScreenString( GetScreenWidth()/2-(w), 60, "vs Computer", 0xffffff, NULL);
		if(menu_item == VS_COMPUTER)
			DrawRectangle(GetScreenWidth()/2-(w), 60+h*2, (GetScreenWidth()/2+(w))*1.038, 63+h*2, 0xffffff, NULL);
	
		TTF_SizeUTF8(font, "vs Player", &w, &h);
		DrawScreenString( GetScreenWidth()/2-(w), 120, "vs Player", 0xffffff, NULL);
		if(menu_item == VS_PLAYER)
			DrawRectangle(GetScreenWidth()/2-(w), 120+h*2, (GetScreenWidth()/2+(w))*1.038, 123+h*2, 0xffffff, NULL);
		SetNextUpdateRect( 0/*X*/, 0/*Y*/, GetScreenWidth(), 150/*Height*/ );
	}
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
	if(!menu){
		m_pBall->SetSpeed(0.1, 0.1);
		m_pBall->SetPosition( iX, iY );
	}
}

/*
Handle any key presses here.
Note that the objects themselves (e.g. player) may also check whether a key is pressed
*/
void BouncingBallMain::KeyDown(int iKeyCode)
{
	switch ( iKeyCode )
	{
	case SDLK_DOWN:
		if(menu){
			if(menu_item < 2){
				menu_item++;
				Redraw(true);
			}
		}
	break;
	case SDLK_UP:
		if(menu){
			if(menu_item > 1){
				menu_item--;
				Redraw(true);
			}
		}
	break;
	case SDLK_RETURN:
		if(menu){
			if(menu_item == VS_COMPUTER){
				this->AddObjects();
			}else if(menu_item == VS_PLAYER){
				this->AddObjects();
			}
			menu = false;
			Redraw(true); // We need to clear the strings from the screen
		}
	break;
	case SDLK_ESCAPE: // End program when escape is pressed
		SetExitWithCode( 0 );
		break;
	case SDLK_SPACE: // SPACE Pauses
		break;
	}
}

