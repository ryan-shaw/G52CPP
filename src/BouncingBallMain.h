#ifndef BouncingBallMain_H
#define BouncingBallMain_H

#include "BaseEngine.h"
// Menu items as well as states
#define VS_COMPUTER 1
#define VS_PLAYER 2
// States
#define MAIN_MENU 3
#define IN_GAME 4
#define GAME_OVER 5

// Forward declarations of classes
// Says that these are classes, but not what the classes look like
// Doesn't matter, since I only use pointers to them, so compiler only
// cares when I de-reference the pointer.
class PlayerWall;
class BouncingBall;

// This includes the class definition for the TileManager class,
// which I use
#include "TileManager.h"

// Class definition for BouncingBallMain
// Says that it subclasses a class called BaseEngine
// so we inherit a lot of functionality for this class
class BouncingBallMain :
	public BaseEngine
{
private:
	TTF_Font* font;
	bool menu;
	int menu_item;
	int state;
	bool AI;

protected:
	// Three member variables, to store pointers to the three balls
	PlayerWall* m_pWall1;
	PlayerWall* m_pWall2;
	BouncingBall* m_pBall;

	// A member object. Object is created when the BouncingBallMain
	// is created
	TileManager m;

public:
	
	//BouncingBall* GetBall(){return m_pBall;}
	/**
	Constructor
	The : here refers to an initialisation list
	*/
	BouncingBallMain()
	: BaseEngine( 6 ) // Pass 6 to superclass constructor
	// Initialise pointers to NULL
	, m_pWall1(NULL)
	, m_pWall2(NULL)
	, m_pBall(NULL)
	, menu_item(VS_COMPUTER)
	, state(MAIN_MENU)
	{}

	// Do any setup of back buffer prior to locking the screen buffer
	// Do the drawing of the background in here and 
	// it'll be copied to the screen for you as needed
	virtual void SetupBackgroundBuffer();
	void StartGame(bool);
	// Create the bouncing ball(s)
	int InitialiseObjects();
	void AddObjects(bool);
	// Draw any strings that you need on the screen
	void DrawStrings();

	// The game logic - move things and change the state if necessary.
	// Must call Redraw(true/false) if anything changes that shows on the screen.
	virtual void GameAction();

	// Mouse-down override
	void MouseDown( int iButton, int iX, int iY );

	// Handle key presses if necessary
	virtual void KeyDown(int iKeyCode);
};

#endif
