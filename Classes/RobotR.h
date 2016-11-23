#ifndef __ROBOTR__
#define __ROBOTR__
#include "cocos2d.h"
using namespace cocos2d;
enum Directions
{
	Left,
	Right,
	Up,
	DoubleUp,
    DoubleLeft,
    DoubleRight
};
enum Movements
{
	NoPass,
	Fall,
	Ok,
	JumpToWall,
	JustOneStep,
	JustTwoSteps,
    FallAtBlock2,
    FallAtBlock3
};
class RobotR
{
public:
	RobotR() {}
	RobotR(Node* rootNode, int mp[10][8]);
    
	ParticleSystemQuad* particleSystem;
	Sprite* sprite;
	Node* rootNode;
	bool Jump(Directions direction);
	bool Move(Directions direction);
	Directions orientation;
    int starX, starY;
	int y=5,x=2;
	int map[10][8];
	int mapSizeX = 8, mapSizeY = 10;
	int nBlocksFall = 0;
    bool isForWin(bool isJumping = false)
    {
        return x == starX && y == starY + isJumping;
    }
private:
	void RunAnimation();
	void analizeCells(int mp[10][8])
	{
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 8; j++)
			{
				if (mp[i][j] == 2)
				{
					x = j;
					y = i;
					mp[i][j] = 0;
				}
                if(mp[i][j] == 3)
                {
                    starX = j;
                    starY = i;
                    mp[i][j] = 0;
                }
				map[i][j] = mp[i][j];
			}
	}
	Movements canGoToRight();
	Movements canGoToLeft();
	Movements canJumpUp();
	Movements canJumpRight();
	Movements canJumpLeft();
	Movements canJumpDoubleUp();
	Movements canDoubleJumpRight();
	Movements canDoubleJumpLeft();
};
#endif
