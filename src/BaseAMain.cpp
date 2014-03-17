#include "BaseAMain.h"
#include "templates.h"

#include "BaseAMain.h"

BaseAMain::BaseAMain(void) : BaseEngine(6)
{
}


BaseAMain::~BaseAMain(void)
{
}


void BaseAMain::SetupBackgroundBuffer(void)
{
	FillBackground( 0x000000 ); 
 
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


void BaseAMain::MouseDown(int iButton, int iX, int iY)
{
	printf( "%d %d\n", iX, iY);
	if ( iButton == SDL_BUTTON_LEFT ) {
		DrawBackgroundRectangle( iX-10, iY-10, iX+10, iY+10, 0xffff00 );
		//SetSDLUpdateRectImmediately( iX-10, iY-10, 21, 21 );
		Redraw(true);
	}else if ( iButton == SDL_BUTTON_RIGHT ) { 
		DrawBackgroundOval( iX-10, iY-10, iX+10, iY+10, 0xff0000 ); 
		//SetSDLUpdateRectImmediately( iX-10, iY-10, 21, 21 ); 
		Redraw(true); 
	} 

}


void BaseAMain::KeyDown(int aKeyCode)
{
	switch(aKeyCode){
	
		case SDLK_SPACE:
		SetupBackgroundBuffer();
		Redraw(true);
		break;
	
	}

}
