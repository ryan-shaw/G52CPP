#include "PlayerWall.h"
//#include "PongMain.h"
class PongMain;
class PlayerWallAI : public PlayerWall
{
public:
	PlayerWallAI(PongMain* pEngine, bool bPos, Ball* pBall);
	~PlayerWallAI();
	void DoUpdate(int);

private:
	PongMain* m_pEngine;
	Ball* m_pBall;
};