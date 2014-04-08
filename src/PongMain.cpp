#include "header.h"

#include "BaseEngine.h"

#include "Ball.h"

#include "PlayerWall.h"

#include "PongMain.h"

#include "PlayerWallAI.h"

void PongMain::SetupBackgroundBuffer()
{
	FillBackground( 0 );

	for ( int iX = 0 ; iX < GetScreenWidth() ; iX++ )
		for ( int iY = 0 ; iY < this->GetScreenHeight() ; iY++ )
			switch( rand()%500 )
			{
			case 0: SetBackgroundPixel( iX, iY, 0xFF0000 ); break;
			case 1: SetBackgroundPixel( iX, iY, 0x00FF00 ); break;
			case 2: SetBackgroundPixel( iX, iY, 0x0000FF ); break;
			case 3: SetBackgroundPixel( iX, iY, 0xFFFF00 ); break;
			case 4: SetBackgroundPixel( iX, iY, 0x00FFFF ); break;
			case 5: SetBackgroundPixel( iX, iY, 0xFF00FF ); break;
		}

}
// Override & 'super' call. So we can load highscore on load.
int PongMain::Initialise(char* strCaption, int iScreenWidth, int iScreenHeigh, char* szFontName, int iFontSize){
	int iResult = BaseEngine::Initialise(strCaption, iScreenWidth, iScreenHeigh, szFontName, iFontSize);
	ifstream is("highscore.txt");
	if(is.is_open())
		is >> m_iHighScore;
	else
		printf("Failed to open highscore file for reading.\n");
	return iResult;
}

int PongMain::InitialiseObjects()
{
	m_Font=TTF_OpenFont("Cornerstone Regular.ttf", 10);
	return 0;
}

void PongMain::StartGame(bool AIFlag){
	AddObjects(AIFlag);
}

void PongMain::AddObjects(bool bAIFlag)
{
	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();

	// Destroy any existing objects
	DestroyOldObjects();

	m_pBall = new Ball( this, 0, 1, 15, 2);
	m_pBall->SetPosition( 100,100 );
	m_pBall->SetSpeed( 0.1, 0.1);

	m_pWall1 = new PlayerWall(this, true);
	if(bAIFlag) // Choose opponent player based on AIflag
		m_pWall2 = new PlayerWallAI(this, false, m_pBall);
	else
		m_pWall2 = new PlayerWall(this, false);

	m_ppDisplayableObjects = new DisplayableObject*[4]; 

	m_ppDisplayableObjects[0] = m_pBall;
	m_ppDisplayableObjects[1] = m_pWall1;
	m_ppDisplayableObjects[2] = m_pWall2;

	m_ppDisplayableObjects[3] = NULL;

}

/* Draw text labels */
void PongMain::DrawStrings()
{
	int w,h; // Helper ints to draw strings in center
	char* text; // Helper char* to draw strings in center
	char buf[128];
	switch(m_iState){
	case MAIN_MENU:
		CopyBackgroundPixels( 0, 0, GetScreenWidth(), 150 );
		text = "Main Menu";
		TTF_SizeUTF8(m_Font, text, &w, &h); // Get text width to draw in center of the screen
		DrawScreenString( GetScreenWidth()/2-(w), 10, text, 0xffffff, NULL );

		text = "vs Computer";
		TTF_SizeUTF8(m_Font, text, &w, &h);
		DrawScreenString( GetScreenWidth()/2-(w), 60, text, 0xffffff, NULL);
		if(m_iMenuItem == VS_COMPUTER)
			DrawRectangle(GetScreenWidth()/2-(w), 60+h*2, (GetScreenWidth()/2+(w))*1.038 /* Scale it correctly */, 63+h*2, 0xffffff, NULL);
	
		text = "vs Player";
		TTF_SizeUTF8(m_Font, text, &w, &h);
		DrawScreenString( GetScreenWidth()/2-(w), 120, text, 0xffffff, NULL);
		if(m_iMenuItem == VS_PLAYER)
			DrawRectangle(GetScreenWidth()/2-(w), 120+h*2, (GetScreenWidth()/2+(w))*1.038, 123+h*2, 0xffffff, NULL);

		text = "High score";
		TTF_SizeUTF8(m_Font, text, &w, &h);
		DrawScreenString( GetScreenWidth()/2-(w), 180, text, 0xffffff, NULL);
		if(m_iMenuItem == HIGH_SCORE)
			DrawRectangle(GetScreenWidth()/2-(w), 180+h*2, (GetScreenWidth()/2+(w))*1.038, 183+h*2, 0xffffff, NULL);
		SetNextUpdateRect( 0, 0, GetScreenWidth(), 150 );
		break;
	case VS_PLAYER: // We want to display the same for both computer and player states
	case VS_COMPUTER:
		CopyBackgroundPixels(10, 0, GetScreenWidth(), GetScreenHeight());
		sprintf(buf, "Score: %d", m_pWall1->GetScore());
		DrawScreenString(10, !m_pWall1->GetPlayer() ? 10 : GetScreenHeight()-50, buf, 0xffffff, NULL);
		sprintf(buf, "Score: %d", m_pWall2->GetScore());
		DrawScreenString(10, !m_pWall2->GetPlayer() ? 10 : GetScreenHeight()-50, buf, 0xffffff, NULL);
		SetNextUpdateRect(10, 0, GetScreenWidth(), GetScreenHeight());
		break;
	case GAME_OVER:
		text = "GAME OVER";
		TTF_SizeUTF8(m_Font, text, &w, &h);
		DrawScreenString(GetScreenWidth()/2-w, GetScreenHeight()/2-h - 50, text, 0xffffff, NULL);

		text = "Press enter to return to main menu";
		TTF_SizeUTF8(m_Font, text, &w, &h);
		DrawScreenString(GetScreenWidth()/2-w-10, GetScreenHeight()/2-h, text, 0xffffff, NULL);
		SetNextUpdateRect(10, 0, GetScreenWidth(), GetScreenHeight());
		break;
	case HIGH_SCORE:
		sprintf(buf, "High score: %d", m_iHighScore);
		TTF_SizeUTF8(m_Font, buf, &w, &h);
		DrawScreenString(GetScreenWidth()/2-w-10, GetScreenHeight()/2-h, buf, 0xffffff, NULL);
		SetNextUpdateRect(10, 0, GetScreenWidth(), GetScreenHeight());
		break;
	}
}

void PongMain::GameOver(bool player /* which player won */){
	
	m_iState = GAME_OVER;
	int iHighScore = m_pWall1->GetScore() > m_pWall2->GetScore() ? m_pWall1->GetScore() : m_pWall2->GetScore(); // Get highscore from finished game
	m_iHighScore = iHighScore > m_iHighScore ? iHighScore : m_iHighScore; // Is highscore higher than the highest score?
	char buf[16];
	sprintf(buf, "%d", m_iHighScore);
	ofstream ofSHighScore("highscore.txt"); 
	if(ofSHighScore.is_open()){
		ofSHighScore << buf; // Write highscore to file
	}else{
		printf("Failed to open highscore file for writing.\n");
	}
	
	ofSHighScore.close();	
}

void PongMain::GameAction()
{
	// If too early to act then do nothing
	if ( !TimeToAct() )
		return;

	// Don't act for another 10 ticks
	SetTimeToAct( 1 );
	if(m_iState != GAME_OVER) // Freezes the game when over
		UpdateAllObjects( GetTime() );
}


void PongMain::MouseDown( int iButton, int iX, int iY )
{
	// Allowed me to move the ball for debug purposes
	/*if(m_iState == VS_PLAYER || m_iState == VS_COMPUTER){ 
		m_pBall->SetSpeed(0.1, 0.1);
		m_pBall->SetPosition( iX, iY );
	}*/
}

void PongMain::KeyDown(int iKeyCode)
{
	switch ( iKeyCode )
	{
	case SDLK_DOWN:
		if(m_iState == MAIN_MENU){
			if(m_iMenuItem < 3){
				m_iMenuItem++;
				Redraw(true);
			}
		}
	break;
	case SDLK_UP:
		if(m_iState == MAIN_MENU){
			if(m_iMenuItem > 1){
				m_iMenuItem--;
				Redraw(true);
			}
		}
	break;
	case SDLK_RETURN:
		switch(m_iState){
		case MAIN_MENU:
			if(m_iMenuItem == VS_COMPUTER){ // Start game vs computer
				this->StartGame(true); 
				m_iState = VS_COMPUTER;
			}else if(m_iMenuItem == VS_PLAYER){ // Start game vs player
				this->StartGame(false);
				m_iState = VS_PLAYER;
			}else if(m_iMenuItem == HIGH_SCORE){ // Open highscore screen
				m_iState = HIGH_SCORE;
			}
			Redraw(true); // We need to clear the strings from the screen
			break;
		case GAME_OVER:
			m_iState = MAIN_MENU;
			//m_ppDisplayableObjects = NULL; // Remove objects
			DestroyOldObjects();
			Redraw(true);
			break;
		case HIGH_SCORE:
			m_iState = MAIN_MENU;
			Redraw(true);
		}
	break;
	case SDLK_ESCAPE: // End program when escape is pressed
		SetExitWithCode( 0 );
		break;
	case SDLK_SPACE: // SPACE Pauses
		break;
	}
}

