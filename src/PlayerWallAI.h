#include "PlayerWall.h"
#include "BouncingBallMain.h"

class PlayerWallAI : public PlayerWall
{
public:
	PlayerWallAI(BouncingBallMain* pEngine, bool pos);
	~PlayerWallAI();
	void DoUpdate(int);

private:
	BouncingBallMain* m_pEngine;
};